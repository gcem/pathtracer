#include "PathTracer.hpp"
#include "Image.hpp"
#include "PNGExporter.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <thread>

namespace PathTracer {
PathTracer::PathTracer()
  : image(0, 0)
{}

void
PathTracer::trace(std::shared_ptr<Objects::Scene> scenePtr)
{
    scene = scenePtr;
    Objects::Surface::intersectionTestEpsilon = scene->intersectionTestEpsilon;

    for (auto cam : scene->cameras) {
        auto imageStartTime = std::chrono::system_clock::now();
        camera = cam.get();
        int w = camera->getWidth();
        int h = camera->getHeight();
        image = Image::Image<unsigned char>(w, h);
        times = std::vector<std::vector<int>>(h, std::vector<int>(w));

#ifdef MULTITHREADED
        tilesX = (w + TILE_SIZE - 1) / TILE_SIZE; // round up
        tilesY = (h + TILE_SIZE - 1) / TILE_SIZE; // round up
        nextTile = 0;
        int threadCount = std::thread::hardware_concurrency();
        std::vector<std::thread> threads(threadCount);
        for (int i = 0; i < threadCount; i++) {
            threads[i] = std::thread(&PathTracer::traceTilesInThread, this);
        }
        for (auto& thread : threads)
            thread.join();
#else
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                tracePixel(x, y);
            }
        }
#endif
        auto timeImageNormalized = createTimeImage();

        Image::PNGExporter exporter;
        exporter.exportImage(image, camera->imageName());
        exporter.exportImage(timeImageNormalized,
                             camera->imageName() + "_time.png");

        auto imageEndTime = std::chrono::system_clock::now();
        std::cout << camera->imageName() << " took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                       imageEndTime - imageStartTime)
                       .count()
                  << " ms" << std::endl;
    }
}

LinearAlgebra::Vec3
PathTracer::rayColor(const Objects::Ray& ray, int remainingDepth)
{
    FloatT minT = std::numeric_limits<FloatT>::infinity();
    LinearAlgebra::Vec3 normal;
    Objects::Surface* closest = nullptr;

    for (auto surface : scene->surfaces) {
        LinearAlgebra::Vec3 tmpNormal;
        FloatT t = surface->intersect(ray, tmpNormal);
        if (t != -1 && t < minT) {
            minT = t;
            normal = tmpNormal;
            closest = surface.get();
        }
    }

    if (!closest)
        return scene->backgroundColor;

    // hit a surface
    auto material = closest->material;

    LinearAlgebra::Vec3 hitPoint =
      ray.origin + ray.direction * minT + normal * scene->shadowRayEpsilon;
    LinearAlgebra::Vec3 color = scene->ambientLight * material.ambient;

    // diffuse and specular shading
    for (auto& light : scene->lights) {
        if (lightVisible(hitPoint, light)) {
            auto lightDir = light.position - hitPoint;
            auto lightDist = lightDir.norm();
            lightDir = lightDir / lightDist;
            auto mid = (lightDir - ray.direction).normalize();
            auto intensity = light.intensity / (lightDist * lightDist);

            auto diffuse = material.diffuse *
                           std::max<FloatT>(0, normal.dot(lightDir)) *
                           intensity;
            auto specular = material.specular *
                            pow(std::max<FloatT>(0, normal.dot(mid)),
                                material.phongExponent) *
                            intensity;

            color += diffuse + specular;
        }
    }

    // mirror reflection
    if (material.type == Objects::Material::Type::Mirror && remainingDepth) {
        auto reflectedDirection =
          ray.direction - normal * (2 * normal.dot(ray.direction));
        auto reflectedRay = Objects::Ray(hitPoint, reflectedDirection);
        auto reflectedColor = rayColor(reflectedRay, remainingDepth - 1);
        color += reflectedColor * material.mirrorReflectance;
    }

    // fresnel reflection on conductors
    if (material.type == Objects::Material::Type::Conductor && remainingDepth) {
        auto reflectedDirection =
          ray.direction - normal * (2 * normal.dot(ray.direction));
        auto reflectedRay = Objects::Ray(hitPoint, reflectedDirection);
        auto reflectedColor = rayColor(reflectedRay, remainingDepth - 1);

        FloatT theta = -1 * ray.direction.dot(normal);
        FloatT squares = material.refractionIndex * material.refractionIndex +
                         material.absorptionIndex * material.absorptionIndex;

        FloatT cosTheta = normal.dot(reflectedRay.direction);
        FloatT cosSq = cosTheta * cosTheta;
        FloatT nCos = 2 * material.refractionIndex * cosTheta;

        // reflectance for s- and p-polarized light
        FloatT rs = (squares - nCos + cosSq) / (squares + nCos + cosSq);
        FloatT rp = (squares * cosSq - nCos + 1) / (squares * cosSq + nCos + 1);

        FloatT reflectionRatio = (rs + rp) / 2;
        color += reflectedColor * reflectionRatio * material.mirrorReflectance;
    }

    // dielectrics
    if (material.type == Objects::Material::Type::Dielectric &&
        remainingDepth) {
        constexpr FloatT VacuumRefractionIndex = 1;
        FloatT ratio = VacuumRefractionIndex / material.refractionIndex;
        FloatT dotP = ray.direction.dot(normal);

        // cosine of leaving angle squared
        FloatT cosSq = 1 - ratio * ratio * (1 - dotP * dotP);

        if (cosSq < 0) {
            // then there is no transmitted ray.
            // could add mirror reflection here but then we shoud also allow
            // nested meshes.
        } else {
            auto refractedDirection =
              ratio * (ray.direction - normal * dotP) - normal * sqrt(cosSq);
            auto refractedRay =
              Objects::Ray(hitPoint - 2 * scene->shadowRayEpsilon * normal,
                           refractedDirection);

            // minimum leaving angle's cosine
            FloatT minCos = sqrt(1 - ratio * ratio);

            LinearAlgebra::Vec3 leavingNormal;
            auto distance = leaveDielectric(
              refractedRay, closest, minCos, leavingNormal, remainingDepth);

            if (remainingDepth >= 0) {
                leavingNormal = leavingNormal * -1;
                FloatT leavingDotP = refractedRay.direction.dot(leavingNormal);
                FloatT leavingCosSq =
                  1 - 1 / (ratio * ratio) * (1 - leavingDotP * leavingDotP);

                refractedRay.direction =
                  1 / ratio *
                    (refractedRay.direction - leavingNormal * leavingDotP) -
                  leavingNormal * sqrt(leavingCosSq);

                auto baseColor = rayColor(refractedRay, remainingDepth);

                LinearAlgebra::Vec3 attenuationCoefficient = {
                    (FloatT)exp(-material.absorptionCoefficient.x * distance),
                    (FloatT)exp(-material.absorptionCoefficient.y * distance),
                    (FloatT)exp(-material.absorptionCoefficient.z * distance)
                };

                color += baseColor * attenuationCoefficient;
            }
        }
    }

    return color;
}

bool
PathTracer::lightVisible(const LinearAlgebra::Vec3& point,
                         const Objects::PointLight& light)
{
    auto lightDir = light.position - point;
    auto ray = Objects::Ray(point, lightDir);

    // lightDir is not normalized. this way, t < 1 means a surface is closer
    // than the light, t > 1 means the surface is behind the light

    for (auto surface : scene->surfaces) {
        LinearAlgebra::Vec3 normal;
        auto t = surface->intersect(ray, normal);
        if (t != -1 && t < 1)
            return false;
    }
    return true;
}

Image::Image<unsigned char>
PathTracer::createTimeImage() const
{
    int width = times[0].size();
    int height = times.size();

    int maxTime = getMaxTime();
    if (!maxTime) {
        // should not happen
        std::cout << "All time measurements are 0" << std::endl;
        maxTime++;
    }

    Image::Image<unsigned char> timeImage(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // integer division!
            unsigned char normalizedTime = times[y][x] * 255 / maxTime;

            // normalizedTime can be higher than 255. see getMaxTime()
            timeImage.setPixel(
              x, y, { std::min<unsigned char>(255, normalizedTime), 0, 0 });
        }
    }

    return timeImage;
}

int
PathTracer::getMaxTime() const
{
    int width = times[0].size();
    int height = times.size();

    int maxTime = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // ignore isolated pixels with very high time. they are probably
            // noise
            int neighborCount = 0;
            if (times[y][x] > 1.2 * times[y][std::max(0, x - 1)])
                neighborCount++;
            if (times[y][x] > 1.2 * times[y][std::min(width - 1, x + 1)])
                neighborCount++;
            if (times[y][x] > 1.2 * times[std::max(0, y - 1)][x])
                neighborCount++;
            if (times[y][x] > 1.2 * times[std::min(height - 1, y + 1)][x])
                neighborCount++;
            if (neighborCount >= 3)
                continue;

            maxTime = std::max(maxTime, times[y][x]);
        }
    }
    return maxTime;
}

void
PathTracer::traceTile(int xMin, int yMin, int width, int height)
{
    for (int y = yMin; y < yMin + height; y++) {
        for (int x = xMin; x < xMin + width; x++) {
            tracePixel(x, y);
        }
    }
}

void
PathTracer::tracePixel(int x, int y)
{
    auto startTime = std::chrono::system_clock::now();
    auto ray = camera->castRay(x, y);
    auto color = rayColor(ray, scene->maxRecursionDepth);

    image.setPixel(x,
                   y,
                   { (unsigned char)std::clamp(color.x, 0.f, 255.f),
                     (unsigned char)std::clamp(color.y, 0.f, 255.f),
                     (unsigned char)std::clamp(color.z, 0.f, 255.f) });
    auto endTime = std::chrono::system_clock::now();

    int microseconds =
      std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)
        .count();
    times[y][x] = microseconds;
}

void
PathTracer::traceTilesInThread()
{
    for (;;) {
        int myTile = nextTile.fetch_add(1);
        if (myTile >= tilesX * tilesY)
            // no more tiles
            return;

        int xLeft = (myTile % tilesX) * TILE_SIZE;
        int yTop = (myTile / tilesX) * TILE_SIZE;
        int xRight =
          std::min(xLeft + TILE_SIZE, camera->getWidth()); // exclusive
        int yBottom =
          std::min(yTop + TILE_SIZE, camera->getHeight()); // exclusive

        for (int y = yTop; y < yBottom; y++) {
            for (int x = xLeft; x < xRight; x++) {
                tracePixel(x, y);
            }
        }
    }
}

FloatT
PathTracer::leaveDielectric(Objects::Ray& ray,
                            Objects::Surface* dielectric,
                            FloatT leavingCos,
                            LinearAlgebra::Vec3& leavingNormal,
                            int& remainingRecursions)
{
    LinearAlgebra::Vec3 normal;
    FloatT distance = 0;
    while (remainingRecursions >= 0) {
        remainingRecursions--;
        auto t = dielectric->intersect(ray, normal);
        if (t == -1) {
            // normally we must hit the surface but just in case
            remainingRecursions = -1;
            return distance;
        }
        distance += t;

        if (normal.dot(ray.direction) > leavingCos) {
            // cosine is larger than leavingCos, so the ray leaves
            ray.origin =
              ray.origin + ray.direction * t + normal * scene->shadowRayEpsilon;
            leavingNormal = normal;
            return distance;
        }

        // ray got reflected inside
        ray.origin =
          ray.origin + ray.direction * t - normal * scene->shadowRayEpsilon;
        ray.direction = ray.direction - 2 * normal.dot(ray.direction) * normal;
    }
    return distance;
}
}
#include "PathTracer.hpp"
#include "Image.hpp"
#include "PNGExporter.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>

namespace PathTracer {
PathTracer::PathTracer() {}

void
PathTracer::trace(Objects::Scene& scene)
{
    for (auto camera : scene.cameras) {
        auto imageStartTime = std::chrono::system_clock::now();
        int w = camera->getWidth();
        int h = camera->getHeight();
        Image::Image<unsigned char> image(w, h);

        // time it takes to draw each pixel
        auto pixelTimes = std::vector<std::vector<int>>(h, std::vector<int>(w));
        int maxTime = 0;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                auto startTime = std::chrono::system_clock::now();
                auto ray = camera->castRay(x, y);
                auto color = rayColor(ray, scene);

                image.setPixel(
                  x,
                  y,
                  { (unsigned char)std::clamp(color.x, 0.f, 255.f),
                    (unsigned char)std::clamp(color.y, 0.f, 255.f),
                    (unsigned char)std::clamp(color.z, 0.f, 255.f) });
                auto endTime = std::chrono::system_clock::now();

                int microseconds =
                  std::chrono::duration_cast<std::chrono::microseconds>(
                    endTime - startTime)
                    .count();
                maxTime = std::max(maxTime, microseconds);
                pixelTimes[y][x] = microseconds;
            }
        }
        auto timeImageNormalized = createTimeImage(pixelTimes, maxTime);

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
PathTracer::rayColor(const Objects::Ray& ray, Objects::Scene& scene)
{
    FloatT minT = std::numeric_limits<FloatT>::infinity();
    LinearAlgebra::Vec3 normal;
    Objects::Material material;

    for (auto surface : scene.surfaces) {
        LinearAlgebra::Vec3 tmpNormal;
        FloatT t =
          surface->intersect(ray, tmpNormal, scene.intersectionTestEpsilon);
        if (t != -1 && t < minT) {
            minT = t;
            normal = tmpNormal;
            material = surface->material;
        }
    }

    if (minT < std::numeric_limits<FloatT>::infinity()) {
        // hit a surface

        // flip normals until we differentiate between front and back faces
        if (ray.direction.dot(normal) > 0)
            normal = normal * -1;

        LinearAlgebra::Vec3 hitPoint =
          ray.origin + ray.direction * minT + normal * scene.shadowRayEpsilon;
        LinearAlgebra::Vec3 color = scene.ambientLight * material.ambient;

        for (auto& light : scene.lights) {
            if (lightVisible(hitPoint, light, scene)) {
                auto lightDir = light.position - hitPoint;
                auto lightDist = lightDir.norm();
                lightDir = lightDir / lightDist;
                auto mid = (lightDir - ray.direction).normalize();
                auto intensity = light.intensity / (lightDist * lightDist);

                auto diffuse =
                  material.diffuse * normal.dot(lightDir) * intensity;
                auto specular = material.specular *
                                pow(normal.dot(mid), material.phongExponent) *
                                intensity;

                color += diffuse + specular;
            }
        }

        return color;
    } else
        return scene.backgroundColor;
}

bool
PathTracer::lightVisible(const LinearAlgebra::Vec3& point,
                         const Objects::PointLight& light,
                         const Objects::Scene& scene)
{
    auto lightDir = light.position - point;
    auto ray = Objects::Ray(point, lightDir);

    // lightDir is not normalized. this way, t < 1 means a surface is closer
    // than the light, t > 1 means the surface is behind the light

    for (auto surface : scene.surfaces) {
        LinearAlgebra::Vec3 normal;
        auto t = surface->intersect(ray, normal, scene.intersectionTestEpsilon);
        if (t != -1 && t < 1)
            return false;
    }
    return true;
}

Image::Image<unsigned char>
PathTracer::createTimeImage(const std::vector<std::vector<int>>& times,
                            int maxTime)
{
    int width = times[0].size();
    int height = times.size();
    float multiplier = 255.f / maxTime;

    Image::Image<unsigned char> image(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char normalizedTime = times[y][x] * multiplier;
            image.setPixel(
              x, y, { normalizedTime, normalizedTime, normalizedTime });
        }
    }

    return image;
}
}
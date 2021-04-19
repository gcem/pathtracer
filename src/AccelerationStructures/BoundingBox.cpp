#include "BoundingBox.hpp"

namespace AccelerationStructures {
FloatT
BoundingBox::intersect(const Objects::Ray& ray,
                       LinearAlgebra::Vec3& normalOut) const
{
    if (hitsBoundingBox(ray))
        return BruteForce::intersect(ray, normalOut);
    else
        return -1;
}

void
BoundingBox::build(std::vector<Objects::Triangle>&& triangles)
{
    createBoundingBox(triangles);
    BruteForce::build(std::move(triangles));
}

bool
BoundingBox::hitsBoundingBox(const Objects::Ray& ray) const
{
    /**
     * We find the interval (txMin, txMax) for which origin + t * direction is
     * between the planes x = xMin and x = xMax.
     *
     * Then, we repeat the same process for other axes. Finally, we check if the
     * intersection of these intervals is empty. If the intersection is not
     * empty, then there are t values for which the point is between all three
     * plane pairs.
     *
     */

    // planes normal to x axis
    FloatT txMin = (xMin - ray.origin.x) / ray.direction.x;
    FloatT txMax = (xMax - ray.origin.x) / ray.direction.x;
    if (txMin > txMax)
        std::swap(txMin, txMax);
    if (txMax < 0)
        // intersections happen behind the ray
        return false;

    // planes normal to y axis
    FloatT tyMin = (yMin - ray.origin.y) / ray.direction.y;
    FloatT tyMax = (yMax - ray.origin.y) / ray.direction.y;
    if (tyMin > tyMax)
        std::swap(tyMin, tyMax);
    if (tyMax < 0)
        // intersections happen behind the ray
        return false;

    // planes normal to z axis
    FloatT tzMin = (zMin - ray.origin.z) / ray.direction.z;
    FloatT tzMax = (zMax - ray.origin.z) / ray.direction.z;
    if (tzMin > tzMax)
        std::swap(tzMin, tzMax);
    if (tzMax < 0)
        // intersections happen behind the ray
        return false;

    FloatT tMin = std::max(txMin, std::max(tyMin, tzMin));
    FloatT tMax = std::min(txMax, std::min(tyMax, tzMax));

    return tMin < tMax;
}

FloatT
BoundingBox::intersectBoundingBox(const Objects::Ray& ray) const
{
    /**
     * See hitsBoundingBox() for an explanation of this process.
     *
     */

    // planes normal to x axis
    FloatT txMin = (xMin - ray.origin.x) / ray.direction.x;
    FloatT txMax = (xMax - ray.origin.x) / ray.direction.x;
    if (txMin > txMax)
        std::swap(txMin, txMax);
    if (txMax < 0)
        // intersections happen behind the ray
        return -1;

    // planes normal to y axis
    FloatT tyMin = (yMin - ray.origin.y) / ray.direction.y;
    FloatT tyMax = (yMax - ray.origin.y) / ray.direction.y;
    if (tyMin > tyMax)
        std::swap(tyMin, tyMax);
    if (tyMax < 0)
        // intersections happen behind the ray
        return -1;

    // planes normal to z axis
    FloatT tzMin = (zMin - ray.origin.z) / ray.direction.z;
    FloatT tzMax = (zMax - ray.origin.z) / ray.direction.z;
    if (tzMin > tzMax)
        std::swap(tzMin, tzMax);
    if (tzMax < 0)
        // intersections happen behind the ray
        return -1;

    FloatT tMin = std::max(txMin, std::max(tyMin, tzMin));
    FloatT tMax = std::min(txMax, std::min(tyMax, tzMax));

    if (tMin >= tMax)
        // no intersection
        return -1;
    if (tMin < 0)
        // inside the box
        return 0;
    return tMin;
}

void
BoundingBox::createBoundingBox(const std::vector<Objects::Triangle>& triangles)
{
    xMin = xMax = triangles.front().v1.x;
    yMin = yMax = triangles.front().v1.y;
    zMin = zMax = triangles.front().v1.z;
    for (auto& triangle : triangles) {
        xMin = std::min(xMin, triangle.v1.x);
        xMin = std::min(xMin, triangle.v2.x);
        xMin = std::min(xMin, triangle.v3.x);
        yMin = std::min(yMin, triangle.v1.y);
        yMin = std::min(yMin, triangle.v2.y);
        yMin = std::min(yMin, triangle.v3.y);
        zMin = std::min(zMin, triangle.v1.z);
        zMin = std::min(zMin, triangle.v2.z);
        zMin = std::min(zMin, triangle.v3.z);

        xMax = std::max(xMax, triangle.v1.x);
        xMax = std::max(xMax, triangle.v2.x);
        xMax = std::max(xMax, triangle.v3.x);
        yMax = std::max(yMax, triangle.v1.y);
        yMax = std::max(yMax, triangle.v2.y);
        yMax = std::max(yMax, triangle.v3.y);
        zMax = std::max(zMax, triangle.v1.z);
        zMax = std::max(zMax, triangle.v2.z);
        zMax = std::max(zMax, triangle.v3.z);
    }
}
}
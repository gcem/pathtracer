#include "BoundingVolumeHierarchy.hpp"

namespace AccelerationStructures {
FloatT
BoundingVolumeHierarchy::intersect(const Objects::Ray& ray,
                                   LinearAlgebra::Vec3& normalOut) const
{
    if (hitsBoundingBox(ray))
        return intersectTriangle(ray, normalOut);
    else
        return -1;
}

void
BoundingVolumeHierarchy::build(std::vector<Objects::Triangle>&& triangles)
{
    createBoundingBox(triangles);

    if (triangles.size() <= BRUTE_FORCE_THRESHOLD) {
        BruteForce::build(std::move(triangles));
        return;
    }

    std::vector<Objects::Triangle> lowTriangles, highTriangles;

    // divide on longest side of the bounding box
    FloatT xLen = xMax - xMin;
    FloatT yLen = yMax - yMin;
    FloatT zLen = zMax - zMin;
    FloatT middle;

    // we invert this variable each time we see a triangle in the middle,
    // so that they are divided evenly. I want to divide them evenly because
    // even if we put all of them to one side, boxes may intersect. This at
    // least makes the tree balanced.
    bool toLeft = false;

    if (xLen > yLen && xLen > zLen) {
        // divide on x
        middle = (xMin + xMax) / 2;
        for (auto& triangle : triangles) {
            if (triangle.v1.x < middle && triangle.v2.x < middle &&
                triangle.v3.x < middle)
                lowTriangles.push_back(triangle);
            else if (triangle.v1.x > middle && triangle.v2.x > middle &&
                     triangle.v3.x > middle)
                highTriangles.push_back(triangle);
            else {
                if (toLeft)
                    lowTriangles.push_back(triangle);
                else
                    highTriangles.push_back(triangle);
                toLeft = !toLeft;
            }
        }
    } else if (yLen > zLen) {
        // divide on y
        middle = (yMin + yMax) / 2;
        for (auto& triangle : triangles) {
            if (triangle.v1.y < middle && triangle.v2.y < middle &&
                triangle.v3.y < middle)
                lowTriangles.push_back(triangle);
            else if (triangle.v1.y > middle && triangle.v2.y > middle &&
                     triangle.v3.y > middle)
                highTriangles.push_back(triangle);
            else {
                if (toLeft)
                    lowTriangles.push_back(triangle);
                else
                    highTriangles.push_back(triangle);
                toLeft = !toLeft;
            }
        }
    } else {
        // divide on z
        middle = (zMin + zMax) / 2;
        for (auto& triangle : triangles) {
            if (triangle.v1.z < middle && triangle.v2.z < middle &&
                triangle.v3.z < middle)
                lowTriangles.push_back(triangle);
            else if (triangle.v1.z > middle && triangle.v2.z > middle &&
                     triangle.v3.z > middle)
                highTriangles.push_back(triangle);
            else {
                if (toLeft)
                    lowTriangles.push_back(triangle);
                else
                    highTriangles.push_back(triangle);
                toLeft = !toLeft;
            }
        }
    }
    if (lowTriangles.size() && highTriangles.size()) {
        left = std::make_unique<BoundingVolumeHierarchy>();
        right = std::make_unique<BoundingVolumeHierarchy>();
        left->build(std::move(lowTriangles));
        right->build(std::move(highTriangles));
    } else {
        BruteForce::build(std::move(triangles));
    }
}

FloatT
BoundingVolumeHierarchy::intersectTriangle(const Objects::Ray& ray,
                                           LinearAlgebra::Vec3& normalOut) const
{
    if (!left && !right)
        return BruteForce::intersect(ray, normalOut);

    FloatT tLeft = left ? left->intersectBoundingBox(ray) : -1;
    FloatT tRight = right ? right->intersectBoundingBox(ray) : -1;

    // didn't hit one of the boxes
    if (tLeft == -1 && tRight == -1)
        return -1;
    if (tLeft == -1)
        return right->intersectTriangle(ray, normalOut);
    if (tRight == -1)
        return left->intersectTriangle(ray, normalOut);

    // hit both boxes
    // test the closer box first
    LinearAlgebra::Vec3 normalLeft, normalRight;
    FloatT tLeftTriangle, tRightTriangle;
    if (tLeft < tRight) {
        // left box is closer
        tLeftTriangle = left->intersectTriangle(ray, normalLeft);
        if (tLeftTriangle == -1)
            return right->intersectTriangle(ray, normalOut);
        if (tLeftTriangle <= tRight) {
            normalOut = normalLeft;
            return tLeftTriangle;
        }
        tRightTriangle = right->intersectTriangle(ray, normalRight);
        if (tRightTriangle == -1 || tLeftTriangle < tRightTriangle) {
            normalOut = normalLeft;
            return tLeftTriangle;
        }
        normalOut = normalRight;
        return tRightTriangle;
    } else {
        // right box is closer
        tRightTriangle = right->intersectTriangle(ray, normalRight);
        if (tRightTriangle == -1)
            return left->intersectTriangle(ray, normalOut);
        if (tRightTriangle <= tLeft) {
            normalOut = normalRight;
            return tRightTriangle;
        }
        tLeftTriangle = left->intersectTriangle(ray, normalLeft);
        if (tLeftTriangle == -1 || tRightTriangle < tLeftTriangle) {
            normalOut = normalRight;
            return tRightTriangle;
        }
        normalOut = normalLeft;
        return tLeftTriangle;
    }
}
}
#include "BruteForce.hpp"

namespace AccelerationStructures {
FloatT
BruteForce::intersect(const Objects::Ray& ray,
                      LinearAlgebra::Vec3& normalOut) const
{
    FloatT minT = std::numeric_limits<FloatT>::infinity();
    for (auto& triangle : triangles) {
        auto t = triangle.intersect(ray);
        if (t != -1 && t < minT) {
            minT = t;
            normalOut = triangle.getNormal();
        }
    }
    return minT < std::numeric_limits<FloatT>::infinity() ? minT : -1;
}

void
BruteForce::build(std::vector<Objects::Triangle>&& triangleVector)
{
    triangles = std::move(triangleVector);
}
}
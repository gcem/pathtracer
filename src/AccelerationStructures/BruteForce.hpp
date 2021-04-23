/**
 * @file BruteForce.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "AccelerationStructure.hpp"
#include <vector>

namespace AccelerationStructures {
/**
 * @brief Finds the intersection by testing the triangles one by one
 *
 */
class BruteForce : public AccelerationStructure
{
public:
    /**
     * @brief Finds the closest intersection in front of the ray
     *
     * Finds the closest intersection with a triangle. If found, returns the t
     * value at intersection and sets normalOut.
     *
     * @param ray Ray to test intersection with
     * @param normalOut If return value is not -1, set to the surface normal at
     * intersection point
     * @return If there was no intersection in front of the ray, -1.
     * Else, a positive t value such that origin + t * direction is on the
     * closest triangle
     */
    FloatT intersect(const Objects::Ray& ray,
                     LinearAlgebra::Vec3& normalOut) const override;

    /**
     * @brief Builds the acceleration structure from a vector of triangles
     *
     * @param triangles Triangles in this acceleration structure. The vector
     * will be destroyed by this function. Use std::move to convert vector to
     * an rvalue.
     */
    void build(std::vector<Objects::Triangle>&& triangles) override;

protected:
    std::vector<Objects::Triangle> triangles;
};
}
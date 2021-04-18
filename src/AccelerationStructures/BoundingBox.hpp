/**
 * @file BoundingBox.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "BruteForce.hpp"

namespace AccelerationStructures {
/**
 * @brief Checks intersection with a bounding box before doing brute-force
 * search
 *
 * Creates an axis-aligned bounding box. Triangles are tested one by one, only
 * for rays that hit the bounding box.
 *
 */
class BoundingBox : public BruteForce
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
     * @return FloatT If there was no intersection in front of the ray, -1.
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
    /**
     * @brief Checks for intersection with bounding box
     *
     * @param ray
     * @return true Ray enters box in positive direction, or the origin of the
     * ray is inside the bounding box
     * @return false Ray doesn't hit the box
     */
    bool hitsBoundingBox(const Objects::Ray& ray) const;

    /**
     * @name Limits
     *
     */
    ///@{
    /**
     * @brief Coordinates of the bounding box
     *
     */
    float xMin, xMax, yMin, yMax, zMin, zMax;
    ///@}
};
}
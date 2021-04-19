/**
 * @file BoundingVolumeHierarchy.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "BoundingBox.hpp"
#include "BruteForce.hpp"
#include <memory>

namespace AccelerationStructures {
/**
 * @brief Checks intersection on a tree of bounding boxes before doing
 * brute-force search
 *
 * Has an axis-aligned bounding box, and two children who are also BVH's.
 * Switches to brute-force test at some point.
 *
 */
class BoundingVolumeHierarchy : public BoundingBox
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
     * @brief Finds the closest intersection in front of the ray without
     * checking bounding box
     *
     * Finds the closest intersection with a triangle. If found, returns the t
     * value at intersection and sets normalOut.
     *
     * It doesn't check intersection with the bounding box. Assumes this was
     * done by its parent.
     *
     * @param ray Ray to test intersection with
     * @param normalOut If return value is not -1, set to the surface normal at
     * intersection point
     * @return FloatT If there was no intersection in front of the ray, -1.
     * Else, a positive t value such that origin + t * direction is on the
     * closest triangle
     */
    FloatT intersectTriangle(const Objects::Ray& ray,
                             LinearAlgebra::Vec3& normalOut) const;

    /**
     * @name Children of this BVH node
     *
     */
    ///@{

    /**
     * @brief Child with lower coordinates along the division axis
     *
     */
    std::unique_ptr<BoundingVolumeHierarchy> left;

    /**
     * @brief Child with higher coordinates along the division axis
     *
     */
    std::unique_ptr<BoundingVolumeHierarchy> right;

    ///@}
};
}
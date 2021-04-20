/**
 * @file KDTree.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "BoundingBox.hpp"
#include "BruteForce.hpp"
#include "KDTreeNode.hpp"
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
class KDTree : public BoundingBox
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
     * @brief Maximum t value for which ray is inside the bounding box
     *
     * This function assumes ray hits the bounding box.
     *
     * @param ray
     * @return FloatT
     */
    FloatT getMaxT(const Objects::Ray& ray) const;

    /**
     * @brief Root of the tree if exists
     *
     */
    std::unique_ptr<KDTreeNode> root;
};
}
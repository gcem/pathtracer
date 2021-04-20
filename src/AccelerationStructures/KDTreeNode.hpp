/**
 * @file KDTreeNode.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "BruteForce.hpp"
#include <memory>

namespace AccelerationStructures {
class KDTreeNode : protected BruteForce
{
public:
    enum class Axis
    {
        x,
        y,
        z
    };

    /**
     * @brief Finds the closest intersection in front of the ray
     *
     * Finds the closest intersection with a triangle. If found, returns the t
     * value at intersection and sets normalOut.
     *
     * @param ray Ray to test intersection with
     * @param normalOut If return value is not -1, set to the surface normal at
     * intersection point
     * @param maxT t value at which we leave the box
     * @return FloatT If there was no intersection in front of the ray, -1.
     * Else, a positive t value such that origin + t * direction is on the
     * closest triangle
     */
    FloatT intersect(const Objects::Ray& ray,
                     LinearAlgebra::Vec3& normalOut,
                     FloatT maxT) const;

    /**
     * @brief Builds the acceleration structure from a vector of triangles
     *
     * Uses the surface area heuristic (tries to make the total surface area of
     * two children close to equal)
     *
     * @param triangles Triangles in this acceleration structure. The vector
     * will be destroyed by this function. Use std::move to convert vector to
     * an rvalue.
     * @param divisionAxis axis to divide the triangles on
     */
    void build(std::vector<Objects::Triangle>&& triangles, Axis divisionAxis);

protected:
    /**
     * @brief Division axis
     *
     */
    Axis divisionAxis;

    /**
     * @brief Coordinate of the division plane perpendicular to divisionAxis
     *
     */
    FloatT divisionPlane;

    /**
     * @name Children of this node
     *
     */
    ///@{

    /**
     * @brief Child with lower coordinates along the division axis
     *
     */
    std::unique_ptr<KDTreeNode> left;

    /**
     * @brief Child with higher coordinates along the division axis
     *
     */
    std::unique_ptr<KDTreeNode> right;

    ///@}
};
}
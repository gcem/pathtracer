/**
 * @file Triangle.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Config.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

namespace Objects {
/**
 * @brief Triangle with front/back faces
 *
 */
class Triangle
{
public:
    /**
     * @brief Construct a new Triangle object
     *
     * Vertices must be given in counterclockwise order, as seen *from* the
     * *front* side of the triangle.
     *
     * @param vertex1
     * @param vertex2
     * @param vertex3
     */
    Triangle(const LinearAlgebra::Vec3& vertex1,
             const LinearAlgebra::Vec3& vertex2,
             const LinearAlgebra::Vec3& vertex3);

    /**
     * @brief Finds the closest intersection of given ray with this triangle.
     *
     * If there is an intersection, returns the t value. Otherwise returns -1.
     * If returned t value is not -1, then ray.origin + ray.direction * t is on
     * the triangle.
     *
     * @param ray
     * @param epsilon Baricentric coordinates are allowed to be in the range
     * (-epsilon, 1 + epsilon) instead of (0, 1)
     * @return FloatT t for the closest intersection with ray, -1 if there is no
     * intersection.
     */
    FloatT intersect(const Ray& ray, FloatT epsilon = 0) const;

    /**
     * @brief Finds if ray intersects this triangle with a t value lower than
     * maxT
     *
     * Looks for an intersection with t in range (0, maxT)
     *
     * @param ray
     * @param maxT Upper limit of t value for intersection test to succeed
     * (exclusive)
     * @param epsilon Baricentric coordinates are allowed to be in the range
     * (-epsilon, 1 + epsilon) instead of (0, 1)
     * @return true This triangle is closer than t
     * @return false There is no intersection in this range
     */
    bool intersectsBefore(const Ray& ray,
                          FloatT maxT,
                          FloatT epsilon = 0) const;

    /**
     * @brief Normal vector
     *
     * @return LinearAlgebra::Vec3 Unit normal vector, facing the front side
     */
    LinearAlgebra::Vec3 getNormal() const;

protected:
    /**
     * @name Vertices
     *
     */
    ///@{
    /**
     * @brief Vertices in counterclockwise order
     *
     */
    LinearAlgebra::Vec3 v1, v2, v3;
    ///@}

    /**
     * @brief Normal vector
     *
     * A unit vector facing the front side, perpendicular to the plane of this
     * triangle
     *
     */
    LinearAlgebra::Vec3 normal;
};
}
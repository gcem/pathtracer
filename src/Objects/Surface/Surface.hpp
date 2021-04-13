/**
 * @file Surface.hpp
 * @author Cem Gundogdu
 * @brief Interface for surfaces that can be hit by rays
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Config.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

namespace Objects {
/**
 * @brief Can be hit by rays, has a material
 *
 */
class Surface
{
public:
    /**
     * @brief Finds the intersection of given ray with this surface.
     *
     * If there is an intersection, returns the t value and sets normalOut.
     * Otherwise returns -1.
     *
     * If return value is not -1, then it is a positive number t such that
     * ray.origin + t * ray.direction is on this surface.
     *
     * @param ray
     * @param normalOut If return value is not -1, then this is set to the
     * surface normal at intersection point. Otherwise unmodified.
     * @param epsilon Allowed precision error to use in intersection tests.
     * Usually makes surfaces larger than they are (or smaller if negative)
     * @return FloatT t for the closest intersection with ray, -1 if there is no
     * intersection.
     */
    virtual FloatT intersect(const Ray& ray,
                             LinearAlgebra::Vec3& normalOut,
                             FloatT epsilon = 0) const = 0;

    /**
     * @brief Finds if ray intersects this surface with a t value lower than
     * maxT
     *
     * Looks for an intersection with t in range (0, maxT)
     *
     * @param ray
     * @param maxT Upper limit of t value for intersection test to succeed
     * (exclusive)
     * @return true There is an intersection closer than t
     * @return false There is no such intersection
     */
    virtual bool intersectsBefore(const Ray& ray,
                                  FloatT maxT,
                                  FloatT epsilon = 0) const = 0;

    /**
     * @brief Material of this Surface
     *
     */
    const Material material;

protected:
    /**
     * @brief Sets the material of Surface
     *
     * @param material
     */
    Surface(const Material& material);
};
}
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
     * @brief Allowed precision error to use in intersection tests
     *
     * Usually makes surfaces larger than they are (or smaller if negative)
     */
    inline static FloatT intersectionTestEpsilon;

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
     * @return FloatT t for the closest intersection with ray, -1 if there is no
     * intersection.
     */
    virtual FloatT intersect(const Ray& ray,
                             LinearAlgebra::Vec3& normalOut) const = 0;

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
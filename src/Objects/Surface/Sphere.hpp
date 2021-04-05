/**
 * @file Sphere.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Ray.hpp"
#include "Surface.hpp"

namespace PathTracer {
class Sphere : public Surface
{
public:
    /**
     * @brief Construct a new Sphere object
     *
     * @param center
     * @param radius
     */
    Sphere(LinearAlgebra::Vec3 center, FloatT radius, Material material);

    /**
     * @brief Finds the closest intersection of given ray with this Sphere.
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
    FloatT intersect(const Ray& ray,
                     LinearAlgebra::Vec3& normalOut) const override;

protected:
    /**
     * @brief Center
     *
     */
    LinearAlgebra::Vec3 center;

    /**
     * @brief Radius
     *
     */
    float radius;
};
}
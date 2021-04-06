/**
 * @file Ray.hpp
 * @author Cem Gundogdu
 * @brief Ray class
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Vector.hpp"

namespace Objects {
/**
 * @brief Ray with an origin and direction
 *
 */
class Ray
{
public:
    /**
     * @brief Construct a new Ray object at the origin
     *
     */
    Ray();

    /**
     * @brief Construct a new Ray object with given origin and direction
     *
     * @param origin
     * @param direction
     */
    Ray(LinearAlgebra::Vec3 origin, LinearAlgebra::Vec3 direction);

    /**
     * @brief Origin (source) of the ray
     *
     */
    LinearAlgebra::Vec3 origin;

    /**
     * @brief Direction of the ray
     *
     * Usually a unit vector but not necessary. Should point in the direction
     * that this ray is extends to. Ray represents *positive* multiples of
     * direction added to origin.
     *
     */
    LinearAlgebra::Vec3 direction;
};
} // namespace Objects
/**
 * @file PointLight.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Vector.hpp"

namespace PathTracer {
/**
 * @brief Has a location and intensity per color channel
 *
 */
class PointLight
{
public:
    /**
     * @brief Construct a new Point Light object
     *
     * @param position
     * @param intensity RGB components of intensity
     */
    PointLight(LinearAlgebra::Vec3 position, LinearAlgebra::Vec3 intensity);

    /**
     * @brief Position
     *
     */
    const LinearAlgebra::Vec3 position;

    /**
     * @brief RGB components of intensity
     *
     */
    const LinearAlgebra::Vec3 intensity;
};
}
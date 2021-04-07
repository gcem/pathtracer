/**
 * @file Scene.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Camera.hpp"
#include "PointLight.hpp"
#include "Surface.hpp"
#include <memory>
#include <vector>

namespace Objects {
/**
 * @brief Has cameras, surfaces and lights
 *
 */
class Scene
{
public:
    /**
     * @brief Cameras
     *
     */
    std::vector<std::shared_ptr<Camera>> cameras;

    /**
     * @brief Surfaces that intersect with rays
     *
     */
    std::vector<std::shared_ptr<Surface>> surfaces;

    /**
     * @brief RGB components of ambient light
     *
     */
    LinearAlgebra::Vec3 ambientLight;

    /**
     * @brief Point lights
     *
     */
    std::vector<PointLight> lights;

    /**
     * @brief RGB components of background color
     *
     */
    LinearAlgebra::Vec3 backgroundColor;

    /**
     * @brief Epsilon for calculating shadow rays
     *
     * Distance to move in normal direction, before doing intersection tests for
     * shadows.
     *
     */
    FloatT shadowRayEpsilon = 0.001;

    /**
     * @brief Epsilon for use in intersection tests
     *
     * Makes triangles a bit larger than they already are, so that there is no
     * space in-between two adjacent triangles.
     *
     */
    FloatT intersectionTestEpsilon = 0.001;
};
}
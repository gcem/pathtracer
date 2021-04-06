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
     * @brief Point lights
     *
     */
    std::vector<PointLight> lights;

    /**
     * @brief RGB components of background color
     *
     */
    LinearAlgebra::Vec3 backgroundColor;
};
}
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

namespace PathTracer {
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
    std::vector<std::unique_ptr<Camera>> cameras;

    /**
     * @brief Surfaces that intersect with rays
     *
     */
    std::vector<std::unique_ptr<Surface>> surfaces;

    /**
     * @brief Point lights
     *
     */
    std::vector<PointLight> lights;
};
}
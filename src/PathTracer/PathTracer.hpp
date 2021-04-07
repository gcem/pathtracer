/**
 * @file PathTracer.hpp
 * @author Cem Gundogdu
 * @brief Core logic of ray tracing
 * @version 1.0
 * @date 2021-04-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Ray.hpp"
#include "Scene.hpp"

namespace PathTracer {
/**
 * @brief Creates images from a Scene object
 *
 */
class PathTracer
{
public:
    /**
     * @brief Construct a new Path Tracer object
     *
     */
    PathTracer();

    /**
     * @brief Create an image for each of the cameras and save it in a file
     *
     * @param scene A scene with at least one camera
     */
    virtual void trace(Objects::Scene& scene);

    /**
     * @brief Find the color seen by given ray
     *
     * @return LinearAlgebra::Vec3
     */
    virtual LinearAlgebra::Vec3 rayColor(const Objects::Ray& ray,
                                         Objects::Scene& scene);

    /**
     * @brief Finds if the given point is illuminated by a point light
     *
     * @param point Point on a surface, after moving epsilon units away from the
     * surface
     * @param light
     * @param scene
     * @return true There is no object between this point and light
     * @return false There is a surface in-between
     */
    virtual bool lightVisible(const LinearAlgebra::Vec3& point,
                              const Objects::PointLight& light,
                              const Objects::Scene& scene);

protected:
    /**
     * @brief Scene currently being rendered
     *
     */
    Objects::Scene scene;
};
}
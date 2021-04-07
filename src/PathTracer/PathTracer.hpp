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

#include "Objects.hpp"

namespace PathTracer {
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
    void trace(Objects::Scene scene);

protected:
    /**
     * @brief Scene currently being rendered
     *
     */
    Objects::Scene scene;

    
};
}
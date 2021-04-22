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

#include "Image.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include <atomic>

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
    virtual void trace(std::shared_ptr<Objects::Scene> scene);

    /**
     * @brief Find the color seen by given ray
     *
     * @param ray
     * @param remainingRecursionDepth How many times this function will follow
     * mirror reflections or refracted rays. Entering and leaving a dielectric
     * is counted as a single step.
     * @return LinearAlgebra::Vec3
     */
    virtual LinearAlgebra::Vec3 rayColor(const Objects::Ray& ray,
                                         int remainingRecursionDepth);

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
                              const Objects::PointLight& light);

protected:
    /**
     * @brief Creates an image where the pixel that took the longest time is
     * white
     *
     * Linearly maps the time range (0, maxTime) to color range (0, 255)
     *
     * @return Image::Image<unsigned int> Normalized image
     */
    Image::Image<unsigned char> createTimeImage() const;

    /**
     * @brief Maximum value in the times matrix
     *
     * @return int Maximum time it took a pixel to render, in microseconds
     */
    int getMaxTime() const;

    /**
     * @brief Finds the pixel colors in a given *width by height* tile
     *
     * Top-left corner of the tile is the pixel (x, y). This function finds all
     * colors, measures times, updates image and times fields of the class.
     *
     * @param xMin x-coordinate of top-left pixel (0-indexed, increases towards
     * right)
     * @param yMin y-coordinate of top-left pixel (0-indexed, increases towards
     * bottom)
     * @param width number of pixels in the tile in horizontal direction
     * @param height number of pixels in the tile in vertical direction
     */
    virtual void traceTile(int xMin, int yMin, int width, int height);

    /**
     * @brief Calculates the color of pixel (x, y) and updates the image and
     * times fields
     *
     * @param x x-coordinate (0-indexed, increases towards right)
     * @param y y-coordinate (0-indexed, increases towards bottom)
     */
    virtual void tracePixel(int x, int y);

    /**
     * @brief Renders the next tile that is not processed, until all tiles are
     * done
     *
     * Renders tile numbered nextTile until there are no more tiles.
     *
     */
    void traceTilesInThread();

    /**
     * @brief Scene currently being rendered
     *
     */
    std::shared_ptr<Objects::Scene> scene;

    /**
     * @brief Camera whose output is currently being rendered
     *
     * Points to a camera in the scene object
     *
     */
    Objects::Camera* camera;

    /**
     * @brief Image created so far
     *
     */
    Image::Image<unsigned char> image;

    /**
     * @brief Time it took to draw each pixel, in microseconds
     *
     */
    std::vector<std::vector<int>> times;

    /**
     * @brief Next tile to be processed by a thread
     *
     * Zero-indexed. Tiles are numbered from left to right, and then top to
     * bottom.
     *
     */
    std::atomic<int> nextTile;

    /**
     * @name Tile Count
     *
     * These are used for multithreading
     *
     */
    ///@{
    /**
     * @brief Total number of tiles that should be rendered, in x-direction
     *
     */
    int tilesX;

    /**
     * @brief Total number of tiles that should be rendered, in y-direction
     *
     */
    int tilesY;
    ///@}
};
}
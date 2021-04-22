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
 * Assumes there are no nested meshes. That is, when a ray enters a mesh, it
 * doesn't collide with another mesh until leaving.
 *
 * This is currently a Ray Tracer. If lots of things have to change while
 * transitioning to Path Tracer, this class should be renamed to RayTracer and a
 * new one should be added.
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
     * mirror reflections or refracted rays. Entering a dielectric, leaving it,
     * and all reflections contribute to the depth.
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
     * @brief Finds where a ray leaves the dielectric and the distance it
     * travels inside
     *
     * Takes a ray that is **inside** the mesh. Follows the reflections until
     * the ray leaves the mesh. Changes the reference parameter to the leaving
     * ray that is **outside** the mesh, but **not** refracted.
     *
     * If the ray doesn't leave the mesh, remainingRecursions is set to -1.
     *
     * Assumes there are no other surfaces inside the dielectric.
     *
     * @param ray Initially, entering ray. On return, this is set to the leaving
     * ray. If remainingRecursions is set to -1, this ray has no meaning on
     * return.
     * @param dielectric Surface that the ray is inside
     * @param remainingRecursions Maximum number of reflections to follow inside
     * the surface. Decremented at each reflection.
     * @return FloatT Distance traveled. If remainingRecursions is set to -1,
     * this has no meaning.
     */
    FloatT leaveDielectric(Objects::Ray& ray,
                           Objects::Surface* dielectric,
                           int& remainingRecursions);

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
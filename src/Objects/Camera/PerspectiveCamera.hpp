/**
 * @file Camera.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Camera.hpp"

namespace PathTracer {
/**
 * @brief Generates rays that form a perspective image of the scene
 *
 * Casts rays from the position of the camera to a plane, on which pixels
 * form a uniform rectangular grid.
 *
 */
class PerspectiveCamera : public Camera
{
    /**
     * @brief Construct a new Perspective Camera object
     *
     * @param gaze Front vector
     * @param up Up vector
     * @param position Position of the camera
     * @param width Resulotion of the created image in horizontal direction
     * @param height Resulotion of the created image in vertical direction
     * @param left Distance of left edge of the image plane to the intersection
     * of gaze and the plane
     * @param right Distance of right edge of the image plane to the
     * intersection of gaze and the plane
     * @param bottom Distance of bottom edge of the image plane to the
     * intersection of gaze and the plane
     * @param top Distance of top edge of the image plane to the intersection of
     * gaze and the plane
     */
    PerspectiveCamera(LinearAlgebra::Vec3 gaze,
                      LinearAlgebra::Vec3 up,
                      LinearAlgebra::Vec3 position,
                      int width,
                      int height,
                      float left,
                      float right,
                      float bottom,
                      float top);

    /**
     * @brief Creates a ray from camera to pixel (x, y) on the image plane
     *
     * @param x x-coordinate of the pixel, leftmost pixel being 0 and rightmost
     * pixel being width - 1
     * @param y y-coordinate of the pixel, top row being 0 and bottom row being
     * height - 1
     * @return Ray Ray from Camera's position to pixel (x, y). Direction of the
     * ray is a unit vector.
     */
    Ray castRay(int x, int y) const override;

protected:
    /**
     * @name Image Plane
     *
     */
    ///@{
    /**
     * @brief Borders of image plane
     *
     * @see PerspectiveCamera constructor for details
     *
     */
    float left, right, bottom, top;
    ///@}
};
}
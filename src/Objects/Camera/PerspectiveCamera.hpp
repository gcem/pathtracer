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

namespace Objects {
/**
 * @brief Generates rays that form a perspective image of the scene
 *
 * Casts rays from the position of the camera to a plane, on which pixels
 * form a uniform rectangular grid.
 *
 */
class PerspectiveCamera : public Camera
{
public:
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
                      float top,
                      float near,
                      float far);

    /**
     * @brief Creates a ray from camera to pixel (x, y) on the image plane
     *
     * Top-left pixel is (0, 0). Bottom-right pixel is (width - 1, height - 1).
     *
     * @param x x-coordinate of the pixel
     * @param y y-coordinate of the pixel
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

    /**
     * @brief Near plane distance
     *
     * Only used to find out what left, right, bottom, top mean. Objects closer
     * than near plane will also be drawn.
     *
     */
    float near;

    /**
     * @brief Far plane distance
     *
     * Will not be used by the Camera itself. We save this in case I/O
     * operations need it later.
     *
     */
    float far;

    /**
     * @brief Vector pointing to right neighbor pixel
     *
     * Vector pointing to right, calculated using up and gaze vectors. Its norm
     * is equal to the width of one pixel on the image plane.
     *
     * If you add this to a vector pointing to pixel (x, y), you get to (x + 1,
     * y)
     *
     */
    LinearAlgebra::Vec3 rightPixel;

    /**
     * @brief Vector pointing to the bottom neighbor pixel
     *
     * Vector pointing to bottom (-up direction). Its norm is equal to the
     * height of one pixel on the image plane.
     *
     * If you add this to a vector pointing to pixel (x, y), you get to (x, y +
     * 1)
     *
     */
    LinearAlgebra::Vec3 bottomPixel;

    /**
     * @brief Vector from position of camera to the center of top-left pixel
     *
     */
    LinearAlgebra::Vec3 topLeft;
};
}
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

#include "Ray.hpp"
#include "Vector.hpp"
#include <string>

namespace Objects {
/**
 * @brief Casts rays to the desired pixel
 *
 */
class Camera
{
public:
    /**
     * @brief Creates a ray from camera to pixel (x, y)
     *
     * Top-left pixel is (0, 0). Bottom-right pixel is (width - 1, height - 1).
     *
     * @param x x-coordinate of the pixel
     * @param y y-coordinate of the pixel
     * @return Ray from Camera's position to pixel (x, y). Direction of the
     * ray is a unit vector.
     */
    virtual Ray castRay(int x, int y) const = 0;

    /**
     * @brief Image Name
     *
     * @return std::string
     */
    std::string imageName() const;

    /**
     * @brief Width of the image to be created
     *
     * @return int
     */
    int getWidth() const;

    /**
     * @brief Height of the image to be created
     *
     * @return int
     */
    int getHeight() const;

    /**
     * @brief Sample count
     *
     * @return int
     */
    int samples() const;

protected:
    /**
     * @brief Construct a new Camera object
     *
     * Creates an orthonormal base from the given vectors. Front (gaze) vector's
     * direction doesn't change. A new up vector is calculated using
     * Gramm-Schmidth orthogonalization.
     *
     * @param imageName Name of image file this camera should create
     * @param gaze Front vector
     * @param up Up vector
     * @param position Position of the camera
     * @param width Resulotion of the created image in horizontal direction
     * @param height Resulotion of the created image in vertical direction
     * @param samples Sample count
     */
    Camera(std::string imageName,
           LinearAlgebra::Vec3 gaze,
           LinearAlgebra::Vec3 up,
           LinearAlgebra::Vec3 position,
           int width,
           int height,
           int samples);

    /**
     * @name Resolution
     *
     */
    ///@{
    /**
     * @brief Resolution
     *
     */
    int width;
    int height;
    ///@}

    /**
     * @brief Sample count
     *
     */
    int sampleCount;

    /**
     * @brief Direction that the Camera is facing
     *
     * A unit vector that points to the front direction of the camera. Usually
     * points to the middle of image surface.
     *
     */
    LinearAlgebra::Vec3 gaze;

    /**
     * @brief Up vector
     *
     * A unit vector that points to the up direction. It is orthogonal to gaze.
     *
     */
    LinearAlgebra::Vec3 up;

    /**
     * @brief Position of Camera
     *
     */
    LinearAlgebra::Vec3 position;

    /**
     * @brief Name of image file this camera should create
     *
     */
    std::string fileName;
};
}
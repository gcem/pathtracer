/**
 * @file Image.hpp
 * @author Cem Gundogdu
 * @brief RGB image with arbitrary pixel type
 * @version 1.0
 * @date 2021-04-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Vector.hpp"
#include <vector>

namespace Image {
/**
 * @brief Holds an RGB image
 *
 * @tparam T Red, green, blue components of a pixel
 */
template<typename T>
class Image
{
public:
    /**
     * @brief Construct a new Image object
     *
     * Allocates an array large enough to store the given image size.
     *
     * @param width
     * @param height
     */
    Image(int width, int height);

    /**
     * @brief Reference to underlying array
     *
     * @return std::vector<T>&
     */
    std::vector<T>& pixelArray();

    /**
     * @brief Get pixel at (x, y)
     *
     * Top-left pixel is (0, 0). x coordinates increase from left to right. y
     * coordinates increase from top to bottom.
     *
     * @param x
     * @param y
     * @return LinearAlgebra::Vec3
     */
    LinearAlgebra::Vec3Template<T, FloatT> getPixel(int x, int y) const;

    /**
     * @brief Set pixel color at (x, y)
     *
     * Top-left pixel is (0, 0). x coordinates increase from left to right. y
     * coordinates increase from top to bottom.
     *
     * @param x
     * @param y
     * @param color
     */
    void setPixel(int x, int y, LinearAlgebra::Vec3Template<T, FloatT> color);

    /**
     * @brief Image width in pixels
     *
     * @return int
     */
    int getWidth() const;

    /**
     * @brief Image height in pixels
     *
     * @return int
     */
    int getHeight() const;

    /**
     * @brief Generates a vector of pointers that each point to the start of a
     * line
     *
     * Returned pointers are valid only until this object's lifetime ends or
     * image size changes
     *
     * @return std::vector<T*>
     */
    std::vector<T*> rowPointers();

protected:
    /**
     * @name Resolution
     *
     */
    ///@{
    /**
     * @brief Resolution of the image
     *
     */
    int width, height;
    ///@}

    /**
     * @brief Array of interleaved red, green, blue values
     *
     */
    std::vector<T> pixels;
};

template<typename T>
Image<T>::Image(int width, int height)
  : width(width)
  , height(height)
{
    pixels = std::vector<T>(width * height * 3);
}

template<typename T>
std::vector<T>&
Image<T>::pixelArray()
{
    return pixels;
}

template<typename T>
LinearAlgebra::Vec3Template<T, FloatT>
Image<T>::getPixel(int x, int y) const
{
    int pos = (y * width + x) * 3;
    return { pixels[pos], pixels[pos + 1], pixels[pos + 2] };
}

template<typename T>
void
Image<T>::setPixel(int x, int y, LinearAlgebra::Vec3Template<T, FloatT> color)
{
    int pos = (y * width + x) * 3;
    pixels[pos] = color.x;
    pixels[pos + 1] = color.y;
    pixels[pos + 2] = color.z;
}

template<typename T>
int
Image<T>::getWidth() const
{
    return width;
}

template<typename T>
int
Image<T>::getHeight() const
{
    return height;
}

template<typename T>
std::vector<T*>
Image<T>::rowPointers()
{
    std::vector<T*> result(height);
    result[0] = &pixels.front();
    for (int i = 1; i < height; i++)
        result[i] = result[i - 1] + width * 3;
    return result;
}
}
/**
 * @file ImageExporter.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Image.hpp"
#include <string>

namespace Image {
/**
 * @brief Saves an Image to a file
 *
 */
class ImageExporter
{
public:
    /**
     * @brief Export image to a file with given name
     *
     * @param image
     * @param filename
     * @return true Success
     * @return false Failure
     */
    virtual bool exportImage(Image<unsigned char>& image,
                             std::string filename) = 0;
};
}
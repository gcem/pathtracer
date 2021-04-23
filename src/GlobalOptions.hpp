/**
 * @file GlobalOptions.hpp
 * @author Cem Gundogdu
 * @brief Options read from arguments to the program
 * @version 1.0
 * @date 2021-04-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <string>

namespace Options {
/**
 * @brief Acceleration structures
 *
 */
enum class AccelerationStructureEnum
{
    BruteForce,
    BoundingBox,
    BoundingVolumeHierarchy,
    KDTree
};

/**
 * @brief Acceleration structure to use with meshes
 *
 */
inline AccelerationStructureEnum accelerationStructure =
  AccelerationStructureEnum::BoundingVolumeHierarchy;

/**
 * @brief Scene file's path
 *
 */
inline std::string sceneFileName;

/**
 * @brief Prefix to add to the camera output file names
 *
 */
inline std::string outputPrefix = "";

/**
 * @brief Minimum number of digits to use in file names in an image sequence
 *
 * For image sequences (scene file names with a '%' character), minimum total
 * number of digits to replace % with
 *
 */
inline int minDigits = 0;
}

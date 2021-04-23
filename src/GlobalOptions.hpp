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
enum class AccelerationStructureEnum
{
    BruteForce,
    BoundingBox,
    BoundingVolumeHierarchy,
    KDTree
};

inline AccelerationStructureEnum accelerationStructure =
  AccelerationStructureEnum::BoundingVolumeHierarchy;
inline std::string sceneFileName;
inline int minDigits = 0;
}

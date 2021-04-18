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
enum AccelerationStructureEnum
{
    BruteForce,
    BoundingBox,
    BoundingVolumeHierarchy
};

inline struct
{
    // TODO: change the default to BVH
    AccelerationStructureEnum accelerationStructure = BoundingBox;
    std::string sceneFileName;
} globalOptions;
}
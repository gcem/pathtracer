/**
 * @file PLYReader.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Config.hpp"
#include "Vector.hpp"
#include <string>
#include <vector>

namespace Parser {
/**
 * @brief Reads vertex data from PLY (polygon) files
 *
 */
class PLYReader
{
public:
    /**
     * @brief Read a PLY file with vertex positions and indices for a triangle
     * mesh
     *
     * Returned values (indices) are exactly the way they appear in the file.
     * This function doesn't care if they are one- or zero-indexed.
     *
     * @param fileName
     * @return std::pair<std::vector<int>, std::vector<FloatT>> Pair of {face
     * vertex indices, vertex coordinates}
     */
    std::pair<std::vector<int>, std::vector<LinearAlgebra::Vec3>> readMesh(
      std::string fileName);
};
}

/**
 * @file Parser.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Scene.hpp"
#include <iostream>

namespace Parser {
/**
 * @brief Parses a file to create a scene object
 *
 * Builder class that creates a Scene object from a file
 *
 */
class Parser
{
public:
    /**
     * @brief Parses the given file to create a Scene object
     *
     * @param file Input file of appropriate format
     * @return Scene Parsed scene object
     */
    virtual PathTracer::Scene parse(std::istream file) const = 0;
};
}
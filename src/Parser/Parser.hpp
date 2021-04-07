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
 * Builder class that creates a Scene object from a file. This class is
 * stateful. Use a new instance for each different scene.
 *
 */
class Parser
{
public:
    /**
     * @brief Parses the given file to create a Scene object
     *
     * @param file Input file of appropriate format
     * @return true On success
     * @return false If file could not be parsed
     */
    virtual bool parse(std::istream& file) = 0;

    /**
     * @brief Get the Scene object created during parse()
     *
     * @return Objects::Scene
     */
    Objects::Scene getScene();

protected:
    /**
     * @brief Scene being generated
     *
     */
    Objects::Scene scene;
};
}
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
     * Also prints the time it took to create the scene. This is useful for
     * measuring the effect of acceleration structures.
     *
     * @param fileName Input file of appropriate format, either relative to
     * current directory or absolute path
     * @return true On success
     * @return false If file could not be parsed
     */
    virtual bool parse(std::string fileName) = 0;

    /**
     * @brief Get the Scene object created during parse()
     *
     * @return Objects::Scene
     */
    std::shared_ptr<Objects::Scene> getScene();

protected:
    /**
     * @brief Scene being generated
     *
     */
    std::shared_ptr<Objects::Scene> scene;
};
}
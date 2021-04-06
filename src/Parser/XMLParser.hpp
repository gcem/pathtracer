/**
 * @file XMLParser.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Parser.hpp"
#include "rapidxml.hpp"

namespace Parser {
/**
 * @brief Parses the XML format used in METU
 *
 * This class is stateful. Use a new instance for each different scene.
 */
class XMLParser : public Parser
{
public:
    /**
     * @brief Construct a new XMLParser object with empty Scene
     *
     */
    XMLParser();

    /**
     * @brief Parses the given XML file to create a Scene object
     *
     * XML file is the format used in METU. It has tags for Scene Epsilon,
     * Cameras, Point Lights, Vertices, Surfaces (Mesh, Triangle, Sphere),
     * Materials and things I can't remember now. This can always be extended as
     * we will be adding more capabilities to the path tracer.
     *
     * @param file Input file of appropriate format
     * @return true On success
     * @return false If file could not be parsed
     */
    bool parse(std::istream& file) override;

protected:
    /**
     * @brief Parses the node that contains entire file content
     *
     * Parses the part of file between <Scene> </Scene> tags, which is the
     * entire scene.
     *
     * @param sceneNode
     * @param scene Object that will be modified after parsing
     * @return Objects::Scene
     */
    void parseSceneNode(rapidxml::xml_node<char>* sceneNode);

    void parseBackgroundColor(rapidxml::xml_node<char>* colorNode);
};
}
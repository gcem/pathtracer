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

namespace Parser {
/**
 * @brief Parses the XML format used in METU
 *
 */
class XMLParser : public Parser
{
public:
    /**
     * @brief Parses the given XML file to create a Scene object
     *
     * XML file is the format used in METU. It has tags for Scene Epsilon,
     * Cameras, Point Lights, Vertices, Surfaces (Mesh, Triangle, Sphere),
     * Materials and things I can't remember now. This can always be extended as
     * we will be adding more capabilities to the path tracer.
     *
     * @param file Input file of appropriate format
     * @return Scene Parsed scene object
     */
    PathTracer::Scene parse(std::istream file) const override;
};
}
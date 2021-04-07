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
    template<typename T = LinearAlgebra::Vec3>
    T readSingleVector(std::string text);
    std::vector<LinearAlgebra::Vec3> readVectorArray(std::string text,
                                                     bool oneIndexed = false);

    template<typename T>
    T readSingleValue(std::string text);

    template<typename T>
    std::vector<T> readArray(std::string text);

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
    virtual void parseSceneNode(rapidxml::xml_node<char>* sceneNode);

    virtual void parseEpsilons(rapidxml::xml_node<char>* sceneNode);
    virtual void parseBackgroundColor(rapidxml::xml_node<char>* colorNode);
    virtual void parseCameras(rapidxml::xml_node<char>* camerasNode);
    virtual void parseCamera(rapidxml::xml_node<char>* cameraNode);
    virtual void parseLights(rapidxml::xml_node<char>* lights);
    virtual void parseAmbientLight(rapidxml::xml_node<char>* ambientLight);
    virtual void parsePointLight(rapidxml::xml_node<char>* pointLight);
    virtual void parseMaterials(rapidxml::xml_node<char>* materials);
    virtual void parseMaterial(rapidxml::xml_node<char>* material);
    virtual void parseVertexData(rapidxml::xml_node<char>* vertices);
    virtual void parseSurfaces(rapidxml::xml_node<char>* surfaces);
    virtual void parseMesh(rapidxml::xml_node<char>* mesh);
    virtual void parseTriangle(rapidxml::xml_node<char>* triangle);
    virtual void parseSphere(rapidxml::xml_node<char>* sphere);

    std::vector<LinearAlgebra::Vec3> vertices;
    std::vector<Objects::Material> materials;
};

template<typename T>
T
XMLParser::readSingleVector(std::string text)
{
    T vector;
    std::istringstream stream(text);
    stream >> vector.x >> vector.y >> vector.z;
    return vector;
}

template<typename T>
T
XMLParser::readSingleValue(std::string text)
{
    T elem;
    std::istringstream stream(text);
    stream >> elem;
    return elem;
}

template<typename T>
std::vector<T>
XMLParser::readArray(std::string text)
{
    T elem;
    std::vector<T> result;
    std::istringstream stream(text);
    while (!(stream >> elem).fail()) {
        result.push_back(elem);
    }
    return result;
}
}
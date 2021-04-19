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
     * @brief Parse the given XML file to create a Scene object
     *
     * XML file is the format used in METU. It has tags for Scene Epsilon,
     * Cameras, Point Lights, Vertices, Surfaces (Mesh, Triangle, Sphere),
     * Materials and things I can't remember now. This can always be extended as
     * we will be adding more capabilities to the path tracer.
     *
     * Also prints the time it took to create the scene. This is useful for
     * measuring the effect of acceleration structures.
     *
     * @param file Input file of appropriate format
     * @return true On success
     * @return false If file could not be parsed
     */
    bool parse(std::istream& file) override;

protected:
    /**
     * @brief Parse a string with 3 numbers as a 3-component vector
     *
     * @tparam T Vector type
     * @param text Text to be parsed
     * @return T Resulting vector
     */
    template<typename T = LinearAlgebra::Vec3>
    T readSingleVector(std::string text);

    /**
     * @brief Convert a string with numbers to vector array, making groups of 3
     *
     * Converts the string "1 2 3 4 5 6" to an array with {1, 2, 3} and {4, 5,
     * 6}.
     *
     * @param text
     * @param oneIndexed Whether the resulting vector should have dummy
     * vector at position 0
     * @return std::vector<LinearAlgebra::Vec3>
     */
    std::vector<LinearAlgebra::Vec3> readVectorArray(std::string text,
                                                     bool oneIndexed = false);

    /**
     * @brief Convert a string to a type that supports istream::operator>>
     *
     * @tparam T Expected type
     * @param text Text to be parsed
     * @return T Resulting object
     */
    template<typename T>
    T readSingleValue(std::string text);

    /**
     * @brief Convert string to vector
     *
     * Converts a string with a list of items to vector of a type that supports
     * istream::operator>>.
     *
     * @tparam T Expected element type
     * @param text Text to be parsed
     * @return std::vector<T> Resulting vector
     */
    template<typename T>
    std::vector<T> readArray(std::string text);

    /**
     * @brief Parse the node that contains entire file content
     *
     * Parses the part of file between \<Scene\> \</Scene\> tags, which is the
     * entire scene.
     *
     * @param sceneNode
     * @return Objects::Scene
     */
    virtual void parseSceneNode(rapidxml::xml_node<char>* sceneNode);

    /**
     * @brief Read epsilon values
     *
     * Parses \<ShadowRayEpsilon\> and \<IntersectionTestEpsilon\> tags inside
     * the given \<Scene\> node.
     *
     * @param sceneNode
     */
    virtual void parseEpsilons(rapidxml::xml_node<char>* sceneNode);

    /**
     * @brief Parse \<BackgroundColor\> node
     *
     * @param colorNode
     */
    virtual void parseBackgroundColor(rapidxml::xml_node<char>* colorNode);

    /**
     * @brief Parse \<Cameras\> node
     *
     * @param camerasNode
     */
    virtual void parseCameras(rapidxml::xml_node<char>* camerasNode);

    /**
     * @brief Parse \<Camera\> node
     *
     * @param cameraNode
     */
    virtual void parseCamera(rapidxml::xml_node<char>* cameraNode);

    /**
     * @brief Parse \<Lights\> node
     *
     * @param lights
     */
    virtual void parseLights(rapidxml::xml_node<char>* lights);

    /**
     * @brief Parse \<AmbientLight\> node
     *
     * @param ambientLight
     */
    virtual void parseAmbientLight(rapidxml::xml_node<char>* ambientLight);

    /**
     * @brief Parse \<PointLight\> node
     *
     * @param pointLight
     */
    virtual void parsePointLight(rapidxml::xml_node<char>* pointLight);

    /**
     * @brief Parse \<Materials\> node
     *
     * @param materials
     */
    virtual void parseMaterials(rapidxml::xml_node<char>* materials);

    /**
     * @brief Parse \<Material\> node
     *
     * @param material
     */
    virtual void parseMaterial(rapidxml::xml_node<char>* material);

    /**
     * @brief Parse \<VertexData\> node
     *
     * Saves the vertices in vertices array of this class. prepends a vector so
     * that the resulting vector is 1-indexed.
     *
     * @param vertexData
     */
    virtual void parseVertexData(rapidxml::xml_node<char>* vertexData);

    /**
     * @brief Parse \<Objects\> node
     *
     * @param surfaces
     */
    virtual void parseSurfaces(rapidxml::xml_node<char>* surfaces);

    /**
     * @brief Parse \<Mesh\> node
     *
     * @param mesh
     */
    virtual void parseMesh(rapidxml::xml_node<char>* mesh);

    /**
     * @brief Parse \<Triangle\> node
     *
     * Creates a mesh with a single triangle
     *
     * @param triangle
     */
    virtual void parseTriangle(rapidxml::xml_node<char>* triangle);

    /**
     * @brief Parse \<Sphere\> node
     *
     * @param sphere
     */
    virtual void parseSphere(rapidxml::xml_node<char>* sphere);

    /**
     * @brief Coordinates of vertices
     *
     * Must be one-indexed due to the format used at METU.
     *
     */
    std::vector<LinearAlgebra::Vec3> vertices;

    /**
     * @brief Materials in the scene
     *
     * Must be one-indexed due to the format used at METU.
     *
     */
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
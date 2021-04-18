#include "XMLParser.hpp"
#include "BoundingBox.hpp"
#include "BruteForce.hpp"
#include "Config.hpp"
#include "GlobalOptions.hpp"
#include "Mesh.hpp"
#include "PerspectiveCamera.hpp"
#include "Sphere.hpp"
#include "rapidxml.hpp"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

namespace Parser {
XMLParser::XMLParser() {}

bool
XMLParser::parse(std::istream& file)
{
    std::vector<char> content(MAX_SCENE_FILE_SIZE);
    file.read(&content.front(), MAX_SCENE_FILE_SIZE - 1);
    rapidxml::xml_document<char> doc;
    try {
        doc.parse<0>(&content.front());
    } catch (rapidxml::parse_error error) {
        std::cout << "XML parse error\n";
        std::cout << error.what() << std::endl;
        return false;
    }
    scene = std::make_shared<Objects::Scene>();
    auto sceneNode = doc.first_node("Scene");
    parseSceneNode(sceneNode);
    return true;
}

std::vector<LinearAlgebra::Vec3>
XMLParser::readVectorArray(std::string text, bool oneIndexed)
{
    LinearAlgebra::Vec3 vec;
    std::vector<LinearAlgebra::Vec3> result;
    std::istringstream stream(text);

    if (oneIndexed)
        result.push_back({});
    while (!(stream >> vec.x).fail()) {
        stream >> vec.y >> vec.z;
        result.push_back(vec);
    }
    return result;
}

void
XMLParser::parseSceneNode(rapidxml::xml_node<char>* sceneNode)
{
    parseEpsilons(sceneNode);
    parseBackgroundColor(sceneNode->first_node("BackgroundColor"));
    parseCameras(sceneNode->first_node("Cameras"));
    parseLights(sceneNode->first_node("Lights"));
    parseMaterials(sceneNode->first_node("Materials"));
    parseVertexData(sceneNode->first_node("VertexData"));
    parseSurfaces(sceneNode->first_node("Objects"));
}

void
XMLParser::parseEpsilons(rapidxml::xml_node<char>* sceneNode)
{
    auto shadow = sceneNode->first_node("ShadowRayEpsilon");
    if (shadow)
        scene->shadowRayEpsilon = readSingleValue<FloatT>(shadow->value());
    auto intersection = sceneNode->first_node("IntersectionTestEpsilon");
    if (intersection)
        scene->intersectionTestEpsilon =
          readSingleValue<FloatT>(intersection->value());
}

void
XMLParser::parseBackgroundColor(rapidxml::xml_node<char>* colorNode)
{
    scene->backgroundColor = readSingleVector(colorNode->value());
}

void
XMLParser::parseCameras(rapidxml::xml_node<char>* camerasNode)
{
    auto camera = camerasNode->first_node("Camera");
    while (camera) {
        parseCamera(camera);
        camera = camera->next_sibling("Camera");
    }
}

void
XMLParser::parseCamera(rapidxml::xml_node<char>* cameraNode)
{
    LinearAlgebra::Vec3 pos =
      readSingleVector(cameraNode->first_node("Position")->value());
    LinearAlgebra::Vec3 gaze =
      readSingleVector(cameraNode->first_node("Gaze")->value());
    LinearAlgebra::Vec3 up =
      readSingleVector(cameraNode->first_node("Up")->value());

    // left right bottom up
    auto planeLRBU =
      readArray<FloatT>(cameraNode->first_node("NearPlane")->value());
    auto planeNear =
      readSingleValue<FloatT>(cameraNode->first_node("NearDistance")->value());

    // width height
    auto resolution =
      readArray<int>(cameraNode->first_node("ImageResolution")->value());
    auto samplesNode = cameraNode->first_node("NumSamples");
    auto samples = samplesNode ? readSingleValue<int>(samplesNode->value()) : 1;

    // trim image name
    std::string imageName = cameraNode->first_node("ImageName")->value();
    imageName.erase(0, imageName.find_first_not_of(' '));
    imageName.erase(imageName.find_last_not_of(' ') + 1);

    auto cam = std::shared_ptr<Objects::Camera>(
      new Objects::PerspectiveCamera(imageName,
                                     gaze,
                                     up,
                                     pos,
                                     resolution[0],
                                     resolution[1],
                                     samples,
                                     planeLRBU[0],
                                     planeLRBU[1],
                                     planeLRBU[2],
                                     planeLRBU[3],
                                     planeNear));
    scene->cameras.push_back(cam);
}

void
XMLParser::parseLights(rapidxml::xml_node<char>* lights)
{
    parseAmbientLight(lights->first_node("AmbientLight"));

    auto pointLight = lights->first_node("PointLight");
    while (pointLight) {
        parsePointLight(pointLight);
        pointLight = pointLight->next_sibling("PointLight");
    }
}

void
XMLParser::parseAmbientLight(rapidxml::xml_node<char>* ambientLight)
{
    scene->ambientLight = readSingleVector(ambientLight->value());
}

void
XMLParser::parsePointLight(rapidxml::xml_node<char>* pointLight)
{
    auto pos = readSingleVector(pointLight->first_node("Position")->value());
    auto intensity =
      readSingleVector(pointLight->first_node("Intensity")->value());
    scene->lights.push_back(Objects::PointLight(pos, intensity));
}

void
XMLParser::parseMaterials(rapidxml::xml_node<char>* materialsNode)
{
    // make one-indexed
    materials = { Objects::Material() };

    auto material = materialsNode->first_node("Material");
    while (material) {
        parseMaterial(material);
        material = material->next_sibling("Material");
    }
}

void
XMLParser::parseMaterial(rapidxml::xml_node<char>* material)
{
    auto ambient =
      readSingleVector(material->first_node("AmbientReflectance")->value());
    auto diffuse =
      readSingleVector(material->first_node("DiffuseReflectance")->value());
    auto specular =
      readSingleVector(material->first_node("SpecularReflectance")->value());
    auto phongNode = material->first_node("PhongExponent");
    auto phongExponent =
      phongNode ? readSingleValue<FloatT>(phongNode->value()) : 1;
    materials.push_back(
      Objects::Material(ambient, diffuse, specular, phongExponent));
}

void
XMLParser::parseVertexData(rapidxml::xml_node<char>* vertexData)
{
    vertices = readVectorArray(vertexData->value(), true);
}

void
XMLParser::parseSurfaces(rapidxml::xml_node<char>* surfaces)
{
    auto surface = surfaces->first_node();
    while (surface) {
        if (strcmp("Mesh", surface->name()) == 0) {
            parseMesh(surface);
        } else if (strcmp("Triangle", surface->name()) == 0) {
            parseTriangle(surface);
        } else if (strcmp("Sphere", surface->name()) == 0) {
            parseSphere(surface);
        } else {
            std::cout << "Unknown surface in parsing: " << surface->name()
                      << std::endl;
        }
        surface = surface->next_sibling();
    }
}

void
XMLParser::parseMesh(rapidxml::xml_node<char>* meshNode)
{
    auto materialIndex =
      readSingleValue<int>(meshNode->first_node("Material")->value());
    auto indices = readArray<int>(meshNode->first_node("Faces")->value());
    std::unique_ptr<AccelerationStructures::AccelerationStructure> acc;
    switch (Options::accelerationStructure) {
        case Options::AccelerationStructureEnum::BruteForce:
            acc = std::make_unique<AccelerationStructures::BruteForce>();
            break;
        case Options::AccelerationStructureEnum::BoundingBox:
            acc = std::make_unique<AccelerationStructures::BoundingBox>();
            break;
            // case Options::AccelerationStructureEnum::BoundingVolumeHierarchy:
            //     acc = std::make_unique<
            //       AccelerationStructures::BoundingVolumeHierarchy>();
            //     break;
    }
    auto mesh = std::shared_ptr<Objects::Surface>(new Objects::Mesh(
      vertices, indices, materials[materialIndex], std::move(acc)));
    scene->surfaces.push_back(mesh);
}

void
XMLParser::parseTriangle(rapidxml::xml_node<char>* triangle)
{
    auto materialIndex =
      readSingleValue<int>(triangle->first_node("Material")->value());
    auto indices = readArray<int>(triangle->first_node("Indices")->value());

    // create a mesh with a single triangle
    auto acc = std::make_unique<AccelerationStructures::BruteForce>();
    auto mesh = std::shared_ptr<Objects::Surface>(new Objects::Mesh(
      vertices, indices, materials[materialIndex], std::move(acc)));
    scene->surfaces.push_back(mesh);
}

void
XMLParser::parseSphere(rapidxml::xml_node<char>* sphereNode)
{
    auto materialIndex =
      readSingleValue<int>(sphereNode->first_node("Material")->value());
    auto centerIndex =
      readSingleValue<int>(sphereNode->first_node("Center")->value());
    auto radius =
      readSingleValue<FloatT>(sphereNode->first_node("Radius")->value());

    auto sphere = std::shared_ptr<Objects::Surface>(new Objects::Sphere(
      vertices[centerIndex], radius, materials[materialIndex]));
    scene->surfaces.push_back(sphere);
}
}
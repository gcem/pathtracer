#include "XMLParser.hpp"
#include "Config.hpp"
#include "rapidxml.hpp"
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
    auto sceneNode = doc.first_node("Scene");
    parseSceneNode(sceneNode);
    return true;
}

void
XMLParser::parseSceneNode(rapidxml::xml_node<char>* sceneNode)
{
    parseBackgroundColor(sceneNode->first_node("BackgroundColor"));
}

void
XMLParser::parseBackgroundColor(rapidxml::xml_node<char>* colorNode)
{
    auto colorText = std::string(colorNode->value());
    std::istringstream stream(colorText);
    stream >> scene.backgroundColor.x >> scene.backgroundColor.y >>
      scene.backgroundColor.z;
}
}
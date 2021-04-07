#include "XMLParser.hpp"
#include <gmock/gmock.h>

namespace Parser {
namespace Test {
class XMLParserMock : public XMLParser
{
public:
    // clang-format off
    MOCK_METHOD(void, parseSceneNode, (rapidxml::xml_node<char>* sceneNode), (override));
    MOCK_METHOD(void, parseBackgroundColor, (rapidxml::xml_node<char>* colorNode), (override));
    MOCK_METHOD(void, parseCameras, (rapidxml::xml_node<char>* camerasNode), (override));
    MOCK_METHOD(void, parseCamera, (rapidxml::xml_node<char>* cameraNode), (override));
    MOCK_METHOD(void, parseLights, (rapidxml::xml_node<char>* lights), (override));
    MOCK_METHOD(void, parseAmbientLight, (rapidxml::xml_node<char>* ambientLight), (override));
    MOCK_METHOD(void, parsePointLight, (rapidxml::xml_node<char>* pointLight), (override));
    MOCK_METHOD(void, parseMaterials, (rapidxml::xml_node<char>* materials), (override));
    MOCK_METHOD(void, parseMaterial, (rapidxml::xml_node<char>* material), (override));
    MOCK_METHOD(void, parseVertexData, (rapidxml::xml_node<char>* vertices), (override));
    MOCK_METHOD(void, parseSurfaces, (rapidxml::xml_node<char>* surfaces), (override));
    MOCK_METHOD(void, parseMesh, (rapidxml::xml_node<char>* mesh), (override));
    MOCK_METHOD(void, parseTriangle, (rapidxml::xml_node<char>* triangle), (override));
    MOCK_METHOD(void, parseSphere, (rapidxml::xml_node<char>* sphere), (override));
    // clang-format on
};
}
}
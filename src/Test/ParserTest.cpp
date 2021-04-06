#include "XMLParser.hpp"
#include "gtest/gtest.h"

namespace Parser {
namespace Test {
TEST(XMLParserTest, Simple)
{
    std::string file =
      R"testfile(
<Scene>
    <BackgroundColor>5 48 220</BackgroundColor>

    <Cameras>
        <Camera id="1">
            <Position>0 0 20</Position>
            <Gaze>0 0 -1</Gaze>
            <Up>0 1 0</Up>
            <NearPlane>-10 10 -10 10</NearPlane>
            <NearDistance>10</NearDistance>
            <ImageResolution>800 800</ImageResolution>
            <ImageName>cornellbox.png</ImageName>
        </Camera>
    </Cameras>

    <Lights>
        <AmbientLight>20 30 40</AmbientLight>
        <PointLight id="1">
            <Position>0 4 2</Position>
            <Intensity>350000 450000 550000</Intensity>
        </PointLight>
    </Lights>

    <Materials>
        <Material id="1">
            <AmbientReflectance>1 1 1</AmbientReflectance>
            <DiffuseReflectance>0.08 0.08 0.08</DiffuseReflectance>
            <SpecularReflectance>0 0 0</SpecularReflectance>
        </Material>
        <Material id="2">
            <AmbientReflectance>1 0 0</AmbientReflectance>
            <DiffuseReflectance>0.1 0 0</DiffuseReflectance>
            <SpecularReflectance>0 0 0</SpecularReflectance>
        </Material>
        <Material id="3">
            <AmbientReflectance>0 0 1</AmbientReflectance>
            <DiffuseReflectance>0 0 0.1</DiffuseReflectance>
            <SpecularReflectance>0 0 0</SpecularReflectance>
        </Material>
        <Material id="4">
            <AmbientReflectance>1 1 1</AmbientReflectance>
            <DiffuseReflectance>0.08 0.08 0.01</DiffuseReflectance>
            <SpecularReflectance>1 1 1</SpecularReflectance>
            <PhongExponent>300</PhongExponent>
        </Material>
        <Material id="5">
            <AmbientReflectance>1 1 1</AmbientReflectance>
            <DiffuseReflectance>0.025 0.125 0.025</DiffuseReflectance>
            <SpecularReflectance>0 0 0</SpecularReflectance>
        </Material>
        <Material id="6">
            <AmbientReflectance>1 1 1</AmbientReflectance>
            <DiffuseReflectance>0.05 0.05 0.05</DiffuseReflectance>
            <SpecularReflectance>0.1 0.1 0.1</SpecularReflectance>
        </Material>
    </Materials>

    <VertexData>
        -10 -10 10
        10 -10 10
        10 10 10
        -10 10 10
        -10 -10 -10
        10 -10 -10
        10 10 -10
        -10 10 -10
        5 -6 1
        -5 -6 -5
    </VertexData>

    <Objects>
        <Mesh id="1">
            <Material>1</Material>
            <Faces>
                1 2 6
                6 5 1
            </Faces>
        </Mesh>
        <Mesh id="2">
            <Material>1</Material>
            <Faces>
                5 6 7
                7 8 5
            </Faces>
        </Mesh>
        <Mesh id="3">
            <Material>1</Material>
            <Faces>
                7 3 4
                4 8 7
            </Faces>
        </Mesh>
        <Mesh id="4">
            <Material>2</Material>
            <Faces>
                8 4 1
                8 1 5		
            </Faces>
        </Mesh>
        <Mesh id="5">
            <Material>3</Material>
            <Faces>
                2 3 7
                2 7 6
            </Faces>
        </Mesh>
        <Sphere id="1">
            <Material>4</Material>
            <Center>9</Center>
            <Radius>4</Radius>
        </Sphere>
        <Sphere id="2">
            <Material>5</Material>
            <Center>10</Center>
            <Radius>4</Radius>
        </Sphere>
    </Objects>
</Scene>
)testfile";
    XMLParser parser;
    std::istringstream stream(file);
    auto scene = parser.parse(stream);
}
}
}
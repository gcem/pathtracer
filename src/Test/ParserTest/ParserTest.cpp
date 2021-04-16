#include "../LinearAlgebraTestCommon.hpp"
#include "XMLParser.hpp"
#include "XMLParserMock.hpp"
#include <fstream>
#include <gtest/gtest.h>

namespace Parser {
namespace Test {
TEST(XMLParserTest, Simple)
{
    XMLParser parser;

    std::ifstream stream("Scenes/SimpleScene.xml");
    auto success = parser.parse(stream);

    EXPECT_TRUE(success);
    auto scene = parser.getScene();

    EXPECT_EQ(LinearAlgebra::Vec3(4, 1, 5), scene->backgroundColor);
    EXPECT_FLOAT_EQ(13e-2, scene->shadowRayEpsilon);
    EXPECT_FLOAT_EQ(18e-1, scene->intersectionTestEpsilon);

    ASSERT_EQ(2, scene->cameras.size());
    EXPECT_EQ("simple.png", scene->cameras[0]->imageName());
    EXPECT_EQ("simple2.png", scene->cameras[1]->imageName());

    ASSERT_EQ(2, scene->lights.size());
    EXPECT_EQ(LinearAlgebra::Vec3(5, 6, 7), scene->lights[0].position);
    EXPECT_EQ(LinearAlgebra::Vec3(1000, 2000, 30.5),
              scene->lights[0].intensity);
    EXPECT_EQ(LinearAlgebra::Vec3(3, 2, 1), scene->lights[1].position);

    LinearAlgebra::Test::EXPECT_VECTOR_EQ(LinearAlgebra::Vec3(25, 35, 45.2),
                                          scene->ambientLight);

    ASSERT_EQ(3, scene->surfaces.size());
    LinearAlgebra::Vec3 amb{ 1, 2, 3 };
    LinearAlgebra::Vec3 dif{ 4, 5, 6 };
    LinearAlgebra::Vec3 spec{ 7, 8, 9 };

    for (auto surface : scene->surfaces) {
        EXPECT_EQ(amb, surface->material.ambient);
        EXPECT_EQ(dif, surface->material.diffuse);
        EXPECT_EQ(spec, surface->material.specular);
        EXPECT_EQ(10, surface->material.phongExponent);
    }
}

class XMLParserUnitTest
  : public ::testing::Test
  , public XMLParser
{
public:
};

TEST_F(XMLParserUnitTest, SingleVector)
{
    auto vec = readSingleVector("5 -2.3 4");
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ 5, -2.3, 4 }, vec);
}

TEST_F(XMLParserUnitTest, VectorArray)
{
    auto arr = readVectorArray("5 -2.3 4 -2 17 9.4");
    ASSERT_EQ(2, arr.size());
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ 5, -2.3, 4 }, arr[0]);
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ -2, 17, 9.4 }, arr[1]);
}

TEST_F(XMLParserUnitTest, VectorArrayOneIndexed)
{
    auto arr = readVectorArray("5 -2.3 4 -2 17 9.4", true);
    ASSERT_EQ(3, arr.size());
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ 5, -2.3, 4 }, arr[1]);
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ -2, 17, 9.4 }, arr[2]);
}

TEST_F(XMLParserUnitTest, SingleValueInt)
{
    auto val = readSingleValue<int>("4");
    EXPECT_EQ(4, val);
}

TEST_F(XMLParserUnitTest, SingleValueFloat)
{
    auto val = readSingleValue<float>("-2.36e1");
    EXPECT_FLOAT_EQ(-23.6, val);
}

TEST_F(XMLParserUnitTest, ValueArray)
{
    auto arr = readArray<float>("5 -2.3 4 -2 17 9.4");
    ASSERT_EQ(6, arr.size());
    EXPECT_EQ(5, arr[0]);
    EXPECT_FLOAT_EQ(-2.3, arr[1]);
    EXPECT_FLOAT_EQ(9.4, arr[5]);
}
}
}
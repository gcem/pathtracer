#include "PLYReader.hpp"
#include "../LinearAlgebraTestCommon.hpp"
#include "Config.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Parser {
namespace Test {
TEST(PLYReaderTest, MeshFile)
{
    PLYReader reader;
    auto result = reader.readMesh("Scenes/SimplePolygons.ply");

    ASSERT_EQ(6, result.indices.size());
    ASSERT_EQ(4, result.vertexPositions.size());

    EXPECT_THAT(result.indices, ::testing::ElementsAre(0, 1, 2, 1, 2, 3));
    std::vector<LinearAlgebra::Vec3> positions = { { -0.4, -0.5, 0.1 },
                                                   { -2.4, 0.5, 0.6 },
                                                   { -3.4, 10.5, 0.7 },
                                                   { -5.7, 15.5, 0.8 } };
    for (int i = 0; i < positions.size(); i++)
        LinearAlgebra::Test::EXPECT_VECTOR_EQ(positions[i],
                                              result.vertexPositions[i]);
}
}
}
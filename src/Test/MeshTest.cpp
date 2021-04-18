#include "Mesh.hpp"
#include "LinearAlgebraTestCommon.hpp"
#include <gtest/gtest.h>

namespace Objects {
namespace Test {
TEST(MeshTest, Material)
{
    LinearAlgebra::Vec3 amb{ 1, 2, 3 };
    LinearAlgebra::Vec3 dif{ 4, 5, 6 };
    LinearAlgebra::Vec3 spec{ 7, 8, 9 };
    Material mat(amb, dif, spec, 2.4);
    Mesh mesh({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }, { 0, 1, 2 }, mat);
    EXPECT_EQ(dif, mesh.material.diffuse);
    EXPECT_EQ(amb, mesh.material.ambient);
    EXPECT_EQ(spec, mesh.material.specular);
    EXPECT_FLOAT_EQ(2.4, mesh.material.phongExponent);
}

class MeshIntersectionTest : public ::testing::Test
{
protected:
    Mesh mesh;
    MeshIntersectionTest()
      : mesh(
          // vertices
          {
            { -5, -5, 0 },
            { -5, 5, 0 },
            { 5, 0, 0 }, // t0
            { -4, -4, 1 },
            { -4, 4, 1 },
            { 4, 0, 1 }, // t1
            { -5, -5, 4 },
            { -5, 5, 4 },
            { 5, 0, 4 }, // t2
            { -5, -5, 10 },
            { -5, 5, 10 },
            { 5, 0, 10 }, // t3
            { -5, -5, 1000 },
            { -5, 5, 1000 },
            { 5, 0, 900 } // t4
          },
          // indices
          { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
          Material())
    {
        Surface::intersectionTestEpsilon = 0;
    }
};

TEST_F(MeshIntersectionTest, Front)
{
    Ray ray({ 0, 0, -3 }, { 0, 0, 1 });
    LinearAlgebra::Vec3 normal;
    auto t = mesh.intersect(ray, normal);
    EXPECT_EQ(3, t);
    EXPECT_EQ(0, normal.x);
    EXPECT_EQ(0, normal.y);
    EXPECT_EQ(-1, normal.z);
}

TEST_F(MeshIntersectionTest, Middle)
{
    Ray ray({ 0, 0, 0.2 }, { 0, 0, 2 });
    LinearAlgebra::Vec3 normal;
    auto t = mesh.intersect(ray, normal);
    EXPECT_FLOAT_EQ(0.4, t);
    EXPECT_EQ(0, normal.x);
    EXPECT_EQ(0, normal.y);
    EXPECT_EQ(-1, normal.z);
}

TEST_F(MeshIntersectionTest, Back)
{
    Ray ray({ 0, 0, -3 }, { 0, 0, -1.5 });
    LinearAlgebra::Vec3 normal;
    auto t = mesh.intersect(ray, normal);
    EXPECT_EQ(-1, t);
}

TEST_F(MeshIntersectionTest, Normal)
{
    Ray ray({ 0, 0, 60 }, { 0, 0, 18 });
    LinearAlgebra::Vec3 normal;
    auto t = mesh.intersect(ray, normal);
    EXPECT_FLOAT_EQ(49.444444444, t) << "Should be (950 - 60) / 18";
    EXPECT_LT(normal.x, 0);
    EXPECT_FLOAT_EQ(0, normal.y);
    EXPECT_LT(normal.z, 0);
}

TEST_F(MeshIntersectionTest, Miss)
{
    Ray ray({ 0, 5.001, 0 }, { 0, 0, 18 });
    LinearAlgebra::Vec3 normal;
    auto t = mesh.intersect(ray, normal);
    EXPECT_EQ(-1, t);
}
}
}
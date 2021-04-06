#include "Triangle.hpp"
#include "LinearAlgebraTestCommon.hpp"
#include <gtest/gtest.h>

namespace Objects {
namespace Test {

TEST(TriangleTest, Normal1)
{
    Triangle tri({ 5, 0, 3 }, { 1, 0, -4 }, { -10, 0, -1 });
    LinearAlgebra::Vec3 nor{ 0, 1, 0 };
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(nor, tri.getNormal());
}

TEST(TriangleTest, Normal2)
{
    Triangle tri({ 5, 0, 3 }, { -10, 0, -1 }, { 1, 0, -4 });
    LinearAlgebra::Vec3 nor{ 0, -1, 0 };
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(nor, tri.getNormal());
}

TEST(TriangleTest, Normal3)
{
    Triangle tri({ 4, 1, -1 }, { 4, 1, 1 }, { 4, 0, 1 });
    LinearAlgebra::Vec3 nor{ 1, 0, 0 };
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(nor, tri.getNormal());
}

TEST(TriangleTest, Intersection1)
{
    Triangle tri({ 4, 1, -1 }, { 4, 1, 1 }, { 4, -1, 0 });
    Ray ray({ 2, -1, -3 }, { 1, 0.5, 1.5 });

    auto t = tri.intersect(ray);
    EXPECT_FLOAT_EQ(2, t);
}

TEST(TriangleTest, Intersection2)
{
    Triangle tri({ 4, 1, -1 }, { 4, 1, 1 }, { 4, -1, 0 });
    Ray ray({ 2, -1, -3 }, LinearAlgebra::Vec3(1, 0.5, 1.5).normalize());

    auto t = tri.intersect(ray);
    EXPECT_FLOAT_EQ(3.741657386773941, t);
}

TEST(TriangleTest, BehindRay)
{
    Triangle tri({ 4, 1, -1 }, { 4, 1, 1 }, { 4, 0, 1 });
    Ray ray({ 2, -1, -3 }, LinearAlgebra::Vec3(1, 0.5, 1.5) * -1.0);

    auto t = tri.intersect(ray);
    EXPECT_EQ(t, -1);
}

TEST(TriangleTest, Miss)
{
    Triangle tri({ 4, 1, -1 }, { 4, 1, 1 }, { 4, 0, 1 });
    Ray ray({ 2, -1, -3 }, LinearAlgebra::Vec3(1, 4.5, 1.5));

    auto t = tri.intersect(ray);
    EXPECT_EQ(t, -1);
}
}
}
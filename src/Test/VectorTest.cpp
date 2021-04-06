#include "Vector.hpp"
#include "LinearAlgebraTestCommon.hpp"
#include <gtest/gtest.h>

namespace LinearAlgebra {
namespace Test {
TEST(VectorTest, DefaultVectorType)
{
    Vec3 vector;
    ::testing::StaticAssertTypeEq<decltype(vector),
                                  Vec3Template<float, float>>();
}

TEST(VectorTest, DefaultConstructor)
{
    Vec3 vector;
    EXPECT_EQ(0, vector.x);
    EXPECT_EQ(0, vector.y);
    EXPECT_EQ(0, vector.z);
}

TEST(VectorTest, InitializerListConstructor)
{
    Vec3 vector{ -2, 4, 7 };
    EXPECT_EQ(-2, vector.x);
    EXPECT_EQ(4, vector.y);
    EXPECT_EQ(7, vector.z);
}

TEST(VectorTest, Constructor)
{
    Vec3 vector(-2, 4, 7);
    EXPECT_EQ(-2, vector.x);
    EXPECT_EQ(4, vector.y);
    EXPECT_EQ(7, vector.z);
}

TEST(VectorTest, ScalarAddition)
{
    Vec3 vector{ 1, 2, 3 };
    auto result = vector + 5;
    EXPECT_EQ(6, result.x);
    EXPECT_EQ(7, result.y);
    EXPECT_EQ(8, result.z);
}

TEST(VectorTest, ScalarSubtraction)
{
    Vec3 vector{ 1, 2, 3 };
    auto result = vector - 5;
    EXPECT_EQ(-4, result.x);
    EXPECT_EQ(-3, result.y);
    EXPECT_EQ(-2, result.z);
}

TEST(VectorTest, ScalarMultiplication)
{
    Vec3 vector{ 1, 2, 3 };
    auto result = vector * 0.5f;
    EXPECT_FLOAT_EQ(0.5, result.x);
    EXPECT_FLOAT_EQ(1, result.y);
    EXPECT_FLOAT_EQ(1.5, result.z);
}

TEST(VectorTest, ScalarDivision)
{
    Vec3 vector{ 1, 2, 3 };
    auto result = vector / 4;
    EXPECT_FLOAT_EQ(0.25, result.x);
    EXPECT_FLOAT_EQ(0.5, result.y);
    EXPECT_FLOAT_EQ(0.75, result.z);
}

TEST(VectorTest, VectorAddition)
{
    Vec3 v1{ 5.7f, 7, -3 };
    Vec3 v2{ 3.3f, 17, 5 };
    auto result = v1 + v2;
    EXPECT_FLOAT_EQ(9, result.x);
    EXPECT_EQ(24, result.y);
    EXPECT_EQ(2, result.z);
}

TEST(VectorTest, VectorSubtraction)
{
    Vec3 v1{ 5.7f, 7, -3 };
    Vec3 v2{ 3.3f, 17, 5 };
    auto result = v1 - v2;
    EXPECT_FLOAT_EQ(2.4, result.x);
    EXPECT_EQ(-10, result.y);
    EXPECT_EQ(-8, result.z);
}

TEST(VectorTest, AdditionAssignment)
{
    Vec3 v1{ 5.7f, 7, -3 };
    Vec3 v2{ 3.3f, 17, 5 };
    auto& result = (v1 += v2);

    EXPECT_FLOAT_EQ(9, v1.x);
    EXPECT_EQ(24, v1.y);
    EXPECT_EQ(2, v1.z);

    v1.x = 300;
    EXPECT_EQ(300, result.x) << "Should return a reference to itself";
}

TEST(VectorTest, SubtractionAssignment)
{
    Vec3 v1{ 5.7f, 7, -3 };
    Vec3 v2{ 3.3f, 17, 5 };
    auto& result = (v1 -= v2);

    EXPECT_FLOAT_EQ(2.4, result.x);
    EXPECT_EQ(-10, result.y);
    EXPECT_EQ(-8, result.z);

    v1.x = 300;
    EXPECT_EQ(300, result.x) << "Should return a reference to itself";
}

TEST(VectorTest, DotProduct)
{
    Vec3 v1{ 5.7f, 7, -3 };
    Vec3 v2{ 3.3f, 17, 5 };
    auto result = v1.dot(v2);
    EXPECT_FLOAT_EQ(122.81, result);
}

TEST(VectorTest, CrossProduct1)
{
    Vec3 v1{ 1, 0, 0 };
    Vec3 v2{ 0, 1, 0 };
    auto result = v1.cross(v2);
    EXPECT_EQ(0, result.x);
    EXPECT_EQ(0, result.y);
    EXPECT_EQ(1, result.z);
}

TEST(VectorTest, CrossProduct2)
{
    Vec3 v1{ 0, 1, 0 };
    Vec3 v2{ 1, 0, 0 };
    auto result = v1.cross(v2);
    EXPECT_EQ(0, result.x);
    EXPECT_EQ(0, result.y);
    EXPECT_EQ(-1, result.z);
}

TEST(VectorTest, CrossProduct3)
{
    Vec3 v1{ 0, 1, 0 };
    Vec3 v2{ 0, 0, 1 };
    auto result = v1.cross(v2);
    EXPECT_EQ(1, result.x);
    EXPECT_EQ(0, result.y);
    EXPECT_EQ(0, result.z);
}

TEST(VectorTest, CrossProduct4)
{
    Vec3 v1{ 1, 1, 1 };
    Vec3 v2{ 2, 2, 2 };
    auto result = v1.cross(v2);
    EXPECT_FLOAT_EQ(0, result.x);
    EXPECT_FLOAT_EQ(0, result.y);
    EXPECT_FLOAT_EQ(0, result.z);
}

TEST(VectorTest, Norm)
{
    Vec3 vec{ 3, -2, 5 };
    EXPECT_FLOAT_EQ(6.164414002968977, vec.norm());
}

TEST(VectorTest, SquaredNorm)
{
    Vec3 vec{ 2, 7, 16.2 };
    auto sqNorm = vec.squaredNorm();
    EXPECT_FLOAT_EQ(315.44, sqNorm);
}

TEST(VectorTest, Normalize)
{
    Vec3 vec{ 1, 2, 3 };
    auto nor = vec.normalize();
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(
      { 0.267261241912424, 0.534522483824849, 0.801783725737273 }, nor);
}

TEST(VectorTest, ComponentMultiplication)
{
    Vec3 vec1{ 3, -2.5, 4 };
    Vec3 vec2{ 4, 7, -5 };
    auto result = vec1 * vec2;
    EXPECT_EQ(12, result.x);
    EXPECT_EQ(-17.5, result.y);
    EXPECT_EQ(-20, result.z);
}
}
}
#include "Vector.hpp"
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
}
}
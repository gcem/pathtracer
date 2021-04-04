#include "Matrix.hpp"
#include "LinearAlgebraTestCommon.hpp"
#include <gtest/gtest.h>

namespace LinearAlgebra {
namespace Test {
TEST(MatrixTest, DefaultConstructor)
{
    Mat3 mat;
    Vec3 col1{ 1, 0, 0 };
    Vec3 col2{ 0, 1, 0 };
    Vec3 col3{ 0, 0, 1 };
    EXPECT_EQ(mat.col1, col1);
    EXPECT_EQ(mat.col2, col2);
    EXPECT_EQ(mat.col3, col3);
}

TEST(MatrixTest, ArrayConstructor)
{
    Mat3 mat({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Vec3 col1{ 1, 2, 3 };
    Vec3 col2{ 4, 5, 6 };
    Vec3 col3{ 7, 8, 9 };
    EXPECT_EQ(mat.col1, col1);
    EXPECT_EQ(mat.col2, col2);
    EXPECT_EQ(mat.col3, col3);
}

TEST(MatrixTest, AutomaticConstructor)
{
    Mat3 mat{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Vec3 col1{ 1, 2, 3 };
    Vec3 col2{ 4, 5, 6 };
    Vec3 col3{ 7, 8, 9 };
    EXPECT_EQ(mat.col1, col1);
    EXPECT_EQ(mat.col2, col2);
    EXPECT_EQ(mat.col3, col3);
}

TEST(MatrixTest, VectorMultiplication)
{
    Mat3 mat{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Vec3 vec{ 3.5, -2, 4.8 };
    auto result = mat * vec;

    EXPECT_FLOAT_EQ(29.1, result.x);
    EXPECT_FLOAT_EQ(35.4, result.y);
    EXPECT_FLOAT_EQ(41.7, result.z);
}

TEST(MatrixTest, MatrixMultiplication)
{
    Mat3 mat1{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    Mat3 mat2{ { 5.5, 2, 8 }, { 3, 3, 7.4 }, { 15, 4, -8 } };
    auto result = mat1 * mat2;
    Vec3 col1{ 69.5, 85, 100.5 };
    Vec3 col2{ 66.8, 80.2, 93.6 };
    Vec3 col3{ -25, -14, -3 };
    EXPECT_EQ(col1, result.col1);
    EXPECT_VECTOR_EQ(col2, result.col2);
    EXPECT_EQ(col3, result.col3);
}

TEST(MatrixTest, Determinant1)
{
    Mat3 mat{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    auto det = mat.determinant();
    EXPECT_EQ(0, det);
}

TEST(MatrixTest, Determinant2)
{
    Mat3 mat{ { 1, 8, 4 }, { -4, 5.72, 6 }, { 7, 8, 9 } };
    auto det = mat.determinant();
    EXPECT_FLOAT_EQ(339.32, det);
}

TEST(MatrixTest, Transpose)
{
    Mat3 mat{ { 1.2, 2, 3 }, { 4, 5, 8.5 }, { 7, 9, 10 } };
    auto trans = mat.transpose();
    Vec3 col1 = { 1.2, 4, 7 };
    Vec3 col2 = { 2, 5, 9 };
    Vec3 col3 = { 3, 8.5, 10 };
    EXPECT_EQ(col1, trans.col1);
    EXPECT_EQ(col2, trans.col2);
    EXPECT_EQ(col3, trans.col3);
}
}
}
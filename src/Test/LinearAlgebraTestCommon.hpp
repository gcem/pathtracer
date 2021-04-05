/**
 * @file LinearAlgebraTestCommon.hpp
 * @author Cem Gundogdu
 * @brief Common utilities for testing
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <Vector.hpp>
#include <gtest/gtest.h>

namespace LinearAlgebra {
namespace Test {
/**
 * @brief Compares v1 and v2 using EXPECT_FLOAT_EQ from GTest
 *
 * @param v1
 * @param v2
 */
void inline EXPECT_VECTOR_EQ(Vec3 v1, Vec3 v2)
{
    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
}
}
}
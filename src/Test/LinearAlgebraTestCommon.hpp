#pragma once

#include <Vector.hpp>
#include <gtest/gtest.h>

namespace LinearAlgebra {
namespace Test {
void inline EXPECT_VECTOR_EQ(Vec3 v1, Vec3 v2)
{
    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
}
}
}
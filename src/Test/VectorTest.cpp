#include "Vector.hpp"
#include <gtest/gtest.h>

namespace LinearAlgebra {
namespace Test {
TEST(VectorTest, DefaultConstructor)
{
    Vec3<float> vector;
    EXPECT_EQ(0, vector.x);
    EXPECT_EQ(0, vector.y);
    EXPECT_EQ(0, vector.z);
}
}
}
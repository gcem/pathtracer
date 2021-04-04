#include "Ray.hpp"
#include <gtest/gtest.h>

namespace PathTracer {
namespace Test {
TEST(RayTest, DefaultConstructor)
{
    Ray ray;
    LinearAlgebra::Vec3 zero{ 0, 0, 0 };
    EXPECT_EQ(zero, ray.origin);
    EXPECT_EQ(1, ray.direction.norm());
}

TEST(RayTest, Constructor)
{
    LinearAlgebra::Vec3 origin{ 3, 2.5, 1 };
    LinearAlgebra::Vec3 dir{ 8, 3, -4.8 };
    Ray ray(origin, dir);
    EXPECT_EQ(origin, ray.origin);
    EXPECT_EQ(dir, ray.direction);
    origin.x = 0;
    dir.x = 0;
    EXPECT_NE(origin, ray.origin);
    EXPECT_NE(dir, ray.direction);
}
}
}
#include "Material.hpp"
#include <gtest/gtest.h>

namespace Objects {
namespace Test {
TEST(MaterialTest, DefaultConstructor)
{
    Material mat;
    LinearAlgebra::Vec3 ones{ 1, 1, 1 };
    EXPECT_EQ(ones, mat.ambient);
    EXPECT_EQ(ones, mat.diffuse);
    EXPECT_EQ(ones, mat.specular);
}

TEST(MaterialTest, Constructor)
{
    LinearAlgebra::Vec3 amb{ 1, 2, 3 };
    LinearAlgebra::Vec3 dif{ 4, 5, 6 };
    LinearAlgebra::Vec3 spec{ 7, 8, 9 };
    Material mat(amb, dif, spec);
    EXPECT_EQ(amb, mat.ambient);
    EXPECT_EQ(dif, mat.diffuse);
    EXPECT_EQ(spec, mat.specular);
}
}
}
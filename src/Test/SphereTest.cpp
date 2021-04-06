#include "Sphere.hpp"
#include "LinearAlgebraTestCommon.hpp"
#include <gtest/gtest.h>

namespace Objects {
namespace Test {
TEST(SphereTest, Material)
{
    LinearAlgebra::Vec3 amb{ 1, 2, 3 };
    LinearAlgebra::Vec3 dif{ 4, 5, 6 };
    LinearAlgebra::Vec3 spec{ 7, 8, 9 };
    Material mat(amb, dif, spec);
    Sphere sphere(LinearAlgebra::Vec3(), 5, mat);
    EXPECT_EQ(dif, sphere.material.diffuse);
    EXPECT_EQ(amb, sphere.material.ambient);
    EXPECT_EQ(spec, sphere.material.specular);
}

TEST(SphereTest, Intersection1)
{
    Sphere sphere({ 2, 0, 0 }, 5, Material());
    Ray ray({ -3, 4, 0 }, { 1, 0, 0 }); // horizontal in +x direction
    LinearAlgebra::Vec3 normal;
    auto t = sphere.intersect(ray, normal);
    EXPECT_FLOAT_EQ(2, t);
    LinearAlgebra::Test::EXPECT_VECTOR_EQ({ -.6, .8, 0 }, normal);
}

TEST(SphereTest, BehindRay)
{
    Sphere sphere({ 2, 2, 2 }, 3, Material());
    Ray ray({ 5, 5, 5 }, { 1, 1, 1 });
    LinearAlgebra::Vec3 normal;
    auto t = sphere.intersect(ray, normal);
    EXPECT_EQ(-1, t);
}

TEST(SphereTest, InsideSphereClose)
{
    Sphere sphere({ 2, 2, 2 }, 3, Material());
    Ray ray({ 3, 3, 3 }, LinearAlgebra::Vec3(1, 1, 1).normalize());
    LinearAlgebra::Vec3 normal;
    auto t = sphere.intersect(ray, normal);
    EXPECT_FLOAT_EQ(1.267949192431123, t) << "Should be 3 - sqrt(3)";
}

TEST(SphereTest, InsideSphereFar)
{
    Sphere sphere({ 2, 2, 2 }, 3, Material());
    Ray ray({ 1, 1, 1 }, { 1, 1, 1 });
    LinearAlgebra::Vec3 normal;
    auto t = sphere.intersect(ray, normal);
    EXPECT_FLOAT_EQ(2.732050807568878, t) << "Should be 3 / sqrt(3) + 1";
}

TEST(SphereTest, NoHit)
{
    Sphere sphere({ 3, 2, 1.7 }, 3, Material());
    Ray ray({ 1, 1.9, 4.8 }, { 0, 0, 1 });
    LinearAlgebra::Vec3 normal;
    auto t = sphere.intersect(ray, normal);
    EXPECT_EQ(-1, t) << "Should be 3 + sqrt(3)";
}
}
}
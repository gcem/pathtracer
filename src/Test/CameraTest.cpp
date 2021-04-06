#include "LinearAlgebraTestCommon.hpp"
#include "PerspectiveCamera.hpp"
#include <gtest/gtest.h>

namespace Objects {
namespace Test {
TEST(PerspectiveCameraTest, FileName)
{
    LinearAlgebra::Vec3 gaze{ 0, 0, -5.5 };
    LinearAlgebra::Vec3 up{ 0, 8, 0 };
    LinearAlgebra::Vec3 pos{ 1, 2, 3 };
    PerspectiveCamera cam(
      "someFile.name", {}, {}, {}, 1, 1, -4, 4, -3, 3, 1, 20);

    EXPECT_EQ("someFile.name", cam.imageName());
}

TEST(PerspectiveCameraTest, SingleRay)
{
    LinearAlgebra::Vec3 gaze{ 0, 0, -5.5 };
    LinearAlgebra::Vec3 up{ 0, 8, 0 };
    LinearAlgebra::Vec3 pos{ 1, 2, 3 };
    PerspectiveCamera cam("", gaze, up, pos, 1, 1, -4, 4, -3, 3, 1, 20);

    auto ray = cam.castRay(0, 0);
    EXPECT_EQ(pos, ray.origin);

    LinearAlgebra::Vec3 dir{ 0, 0, -1 };
    EXPECT_EQ(dir, ray.direction);
}

TEST(PerspectiveCameraTest, ManyRays)
{
    LinearAlgebra::Vec3 gaze{ 0, 0, -5 };
    LinearAlgebra::Vec3 up{ 0, 8, 0 };
    LinearAlgebra::Vec3 pos{ 1, 2, 3 };
    PerspectiveCamera cam("", gaze, up, pos, 3, 3, -3, 3, -3, 3, 1, 20);

    auto topRight = cam.castRay(2, 0);
    auto bottomLeft = cam.castRay(0, 2);
    auto bottomRight = cam.castRay(2, 2);

    LinearAlgebra::Vec3 dirTR{ 2, 2, -1 };
    LinearAlgebra::Vec3 dirBL{ -2, -2, -1 };
    LinearAlgebra::Vec3 dirBR{ 2, -2, -1 };

    LinearAlgebra::Test::EXPECT_VECTOR_EQ(dirTR.normalize(),
                                          topRight.direction);
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(dirBL.normalize(),
                                          bottomLeft.direction);
    LinearAlgebra::Test::EXPECT_VECTOR_EQ(dirBR.normalize(),
                                          bottomRight.direction);
}
}
}
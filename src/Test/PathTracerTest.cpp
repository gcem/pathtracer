#include "PathTracer.hpp"
#include <gtest/gtest.h>

namespace PathTracer {
namespace Test {
class PathTracerTest
  : public ::testing::Test
  , public PathTracer
{};

TEST_F(PathTracerTest, TimeImageNormalization)
{
    times = { { 20, 40, 50 }, { 60, 100, 55 } };
    auto result = createTimeImage();
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(51, 0, 0),
              result.getPixel(0, 0));
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(102, 0, 0),
              result.getPixel(1, 0));
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(140, 0, 0),
              result.getPixel(2, 1)); // 140 = 55 / 100 * 255
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(255, 0, 0),
              result.getPixel(1, 1));
}
}
}
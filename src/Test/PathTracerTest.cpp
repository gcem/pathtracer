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
    std::vector<std::vector<int>> times = { { 20, 40, 50 }, { 60, 100, 55 } };
    auto result = createTimeImage(times, 100);
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(51, 51, 51),
              result.getPixel(0, 0));
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(102, 102, 102),
              result.getPixel(1, 0));
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(140, 140, 140),
              result.getPixel(2, 1)); // 140 = 55 / 100 * 255
    EXPECT_EQ(Image::Image<unsigned char>::PixelT(255, 255, 255),
              result.getPixel(1, 1));
}
}
}
#include "PerspectiveCamera.hpp"
#include "Config.hpp"

namespace Objects {
PerspectiveCamera::PerspectiveCamera(std::string imageName,
                                     LinearAlgebra::Vec3 gaze,
                                     LinearAlgebra::Vec3 up,
                                     LinearAlgebra::Vec3 position,
                                     int width,
                                     int height,
                                     int samples,
                                     float left,
                                     float right,
                                     float bottom,
                                     float top,
                                     float near)
  : Camera(imageName, gaze, up, position, width, height, samples)
  , left(left)
  , right(right)
  , bottom(bottom)
  , top(top)
  , near(near)
{
    auto rightUnitVector = this->gaze.cross(this->up);
    auto w = right - left;
    auto h = top - bottom;

    rightPixel = rightUnitVector * (w / width);
    bottomPixel = this->up * (-h / height);

    topLeft = this->gaze * near + rightUnitVector * (left + (w / width / 2)) +
              this->up * (top - (h / height / 2));
}

Ray
PerspectiveCamera::castRay(int x, int y) const
{
    return Ray(
      position,
      (topLeft + (FloatT)x * rightPixel + (FloatT)y * bottomPixel).normalize());
}
}
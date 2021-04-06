#include "Camera.hpp"

namespace Objects {
Camera::Camera(LinearAlgebra::Vec3 gaze,
               LinearAlgebra::Vec3 up,
               LinearAlgebra::Vec3 position,
               int width,
               int height)
  : position(position)
  , width(width)
  , height(height)
{
    this->gaze = gaze.normalize();
    auto upGazeComp = up.dot(this->gaze);
    this->up = (up - this->gaze * upGazeComp).normalize();
}
}
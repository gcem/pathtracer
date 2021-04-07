#include "Camera.hpp"

namespace Objects {
std::string
Camera::imageName() const
{
    return fileName;
}

int
Camera::samples() const
{
    return sampleCount;
}

Camera::Camera(std::string imageName,
               LinearAlgebra::Vec3 gaze,
               LinearAlgebra::Vec3 up,
               LinearAlgebra::Vec3 position,
               int width,
               int height,
               int samples)
  : position(position)
  , width(width)
  , height(height)
  , sampleCount(samples)
  , fileName(imageName)
{
    this->gaze = gaze.normalize();
    auto upGazeComp = up.dot(this->gaze);
    this->up = (up - this->gaze * upGazeComp).normalize();
}
}
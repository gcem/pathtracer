#include "Ray.hpp"

namespace Objects {
Ray::Ray()
  : direction(0, 0, -1)
{}

Ray::Ray(LinearAlgebra::Vec3 origin, LinearAlgebra::Vec3 direction)
  : origin(origin)
  , direction(direction)
{}
} // namespace Objects
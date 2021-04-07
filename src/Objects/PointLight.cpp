#include "PointLight.hpp"

namespace Objects {
PointLight::PointLight(LinearAlgebra::Vec3 position,
                       LinearAlgebra::Vec3 intensity)
  : position(position)
  , intensity(intensity)
{}
}
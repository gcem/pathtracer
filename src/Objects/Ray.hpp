#pragma once

#include "Vector.hpp"

namespace PathTracer {
class Ray
{
  public:
    /**
     * @brief Construct a new Ray object at the origin
     *
     */
    Ray();

    /**
     * @brief Construct a new Ray object with given origin and direction
     *
     * @param origin
     * @param direction
     */
    Ray(LinearAlgebra::Vec3 origin, LinearAlgebra::Vec3 direction);

    LinearAlgebra::Vec3 origin, direction;
};
} // namespace PathTracer
#pragma once

#include "Vector.hpp"

namespace PathTracer {
template<typename T = float>
class Ray
{
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
    Ray(LinearAlgebra::Vec3<T> origin, LinearAlgebra::Vec3<T> direction);

    LinearAlgebra::Vec3<T> origin, direction;
};
} // namespace PathTracer
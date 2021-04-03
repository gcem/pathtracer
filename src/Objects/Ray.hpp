#include "Vector.hpp"

template <typename T = float>
class Ray {
    Ray();
    Ray(Vec3<T> origin, Vec3<T> direction);

    Vec3<T> origin, direction;
};
#include "Vector.hpp"

namespace LinearAlgebra {
template<typename T>
Vec3<T>::Vec3()
  : x(0)
  , y(0)
  , z(0)
{}

template<typename T>
Vec3<T>::Vec3(T x, T y, T z)
{}

template<typename T>
Vec3<T>::Vec3(std::initializer_list<T> il)
{}
}
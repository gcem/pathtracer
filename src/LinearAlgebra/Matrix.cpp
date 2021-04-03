#include "Matrix.hpp"

namespace LinearAlgebra {
template<typename T>
Mat3<T>::Mat3()
{}

template<typename T>
Mat3<T>::Mat3(Vec3<T> col1, Vec3<T> col2, Vec3<T> col3)
{}

template<typename T>
Mat3<T>::Mat3(std::initializer_list<T> il)
{}

template<typename T>
T
Mat3<T>::determinant()
{}

template<typename T>
Vec3<T>
Mat3<T>::operator*(Vec3<T>& vec)
{}

template<typename T>
Mat3<T>
Mat3<T>::operator*(Mat3<T>& other)
{}

}
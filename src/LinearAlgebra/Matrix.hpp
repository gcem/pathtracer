#pragma once

#include "Vector.hpp"
#include <array>

namespace LinearAlgebra {
/**
 * @brief 3x3 matrix
 *
 * @tparam T Column type
 */
template<typename T>
class Mat3Template
{
    /**
     * @brief Construct a new identity matrix
     *
     */
    Mat3Template();

    /**
     * @brief Construct a new matrix with given vectors as columns
     *
     * @param col1
     * @param col2
     * @param col3
     */
    Mat3Template(T col1, T col2, T col3);

    /**
     * @brief Construct a new Mat 3 object with given elements
     *
     * @param il Elements of the matrix in row-major order (i.e. a11, a12,
     * a13, a21, ...)
     */
    Mat3Template(std::array<T, 9> il);

    /**
     * @brief Calculates the determinant of this matrix
     *
     * @return T determinant
     */
    T determinant();

    /**
     * @brief Matrix multiplication
     *
     * @param other
     * @return Mat3Template<T> this * other
     */
    Mat3Template<T> operator*(Mat3Template<T>& other);

    /**
     * @brief Matrix-Vector multiplication
     *
     * @param vec
     * @return T this * vec
     */
    T operator*(T& vec);

    T col1, col2, col3;
};

template<typename T>
Mat3Template<T>::Mat3Template()
{}

template<typename T>
Mat3Template<T>::Mat3Template(T col1, T col2, T col3)
{}

template<typename T>
Mat3Template<T>::Mat3Template(std::array<T, 9> il)
{}

template<typename T>
T
Mat3Template<T>::determinant()
{}

template<typename T>
T
Mat3Template<T>::operator*(T& vec)
{}

template<typename T>
Mat3Template<T>
Mat3Template<T>::operator*(Mat3Template<T>& other)
{}

using Mat3 = Mat3Template<Vec3>;
using Mat3f = Mat3Template<Vec3f>;
using Mat3d = Mat3Template<Vec3d>;
} // namespace LinearAlgebra
#pragma once

#include "Vector.hpp"
#include <initializer_list>

namespace LinearAlgebra {
template<typename T = float>
class Mat3
{
    /**
     * @brief Construct a new identity matrix
     *
     */
    Mat3();

    /**
     * @brief Construct a new matrix with given vectors as columns
     *
     * @param col1
     * @param col2
     * @param col3
     */
    Mat3(Vec3<T> col1, Vec3<T> col2, Vec3<T> col3);

    /**
     * @brief Construct a new Mat 3 object with given elements
     *
     * @param il Elements of the matrix in row-major order (i.e. a11, a12,
     * a13, a21, ...)
     */
    Mat3(std::initializer_list<T> il);

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
     * @return Mat3<T> this * other
     */
    Mat3<T> operator*(Mat3<T>& other);

    /**
     * @brief Matrix-Vector multiplication
     *
     * @param vec
     * @return Vec3<T> this * vec
     */
    Vec3<T> operator*(Vec3<T>& vec);

    Vec3<T> col1, col2, col3;
};
} // namespace LinearAlgebra
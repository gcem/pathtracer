#pragma once

#include "Vector.hpp"
#include <array>

namespace LinearAlgebra {
/**
 * @brief 3x3 matrix
 *
 * @tparam ColumnT Column type
 */
template<typename ColumnT>
class Mat3Template
{
  public:
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
    Mat3Template(ColumnT col1, ColumnT col2, ColumnT col3);

    /**
     * @brief Construct a new Mat 3 object with given elements
     *
     * @param il Elements of the matrix in column-major order (i.e. a11, a21,
     * a31, a12, ...)
     */
    Mat3Template(const std::array<typename ColumnT::ComponentType, 9>& il);

    /**
     * @brief Calculates the determinant of this matrix
     *
     * @return T determinant
     */
    typename ColumnT::ComponentType determinant() const;

    /**
     * @brief Matrix multiplication
     *
     * @param other
     * @return Mat3Template<ColumnT> this * other
     */
    Mat3Template<ColumnT> operator*(const Mat3Template<ColumnT>& other) const;

    /**
     * @brief Transpose operation
     *
     * @return Mat3Template<ColumnT> Transpose of this matrix
     */
    Mat3Template<ColumnT> transpose() const;

    /**
     * @brief Matrix-Vector multiplication
     *
     * @param vec
     * @return ColumnT this * vec
     */
    ColumnT operator*(const ColumnT& vec) const;

    ColumnT col1, col2, col3;
};

template<typename ColumnT>
Mat3Template<ColumnT>::Mat3Template()
  : Mat3Template({ 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 })
{}

template<typename ColumnT>
Mat3Template<ColumnT>::Mat3Template(ColumnT col1, ColumnT col2, ColumnT col3)
  : col1(col1)
  , col2(col2)
  , col3(col3)
{}

template<typename ColumnT>
Mat3Template<ColumnT>::Mat3Template(
  const std::array<typename ColumnT::ComponentType, 9>& il)
  : col1({ il[0], il[1], il[2] })
  , col2({ il[3], il[4], il[5] })
  , col3({ il[6], il[7], il[8] })
{}

template<typename ColumnT>
typename ColumnT::ComponentType
Mat3Template<ColumnT>::determinant() const
{
    return col1.x * (col2.y * col3.z - col2.z * col3.y) -
           col1.y * (col2.x * col3.z - col2.z * col3.x) +
           col1.z * (col2.x * col3.y - col2.y * col3.x);
}

template<typename ColumnT>
Mat3Template<ColumnT>
Mat3Template<ColumnT>::transpose() const
{
    return Mat3Template<ColumnT>({ col1.x,
                                   col2.x,
                                   col3.x,
                                   col1.y,
                                   col1.y,
                                   col1.y,
                                   col1.z,
                                   col2.z,
                                   col3.z });
}

template<typename ColumnT>
ColumnT
Mat3Template<ColumnT>::operator*(const ColumnT& vec) const
{
    return vec.x * col1 + vec.y * col2 + vec.z * col3;
}

template<typename ColumnT>
Mat3Template<ColumnT>
Mat3Template<ColumnT>::operator*(const Mat3Template<ColumnT>& other) const
{
    return { *this * other.col1, *this * other.col2, *this * other.col3 };
}

using Mat3 = Mat3Template<Vec3>;
using Mat3f = Mat3Template<Vec3f>;
using Mat3d = Mat3Template<Vec3d>;
} // namespace LinearAlgebra
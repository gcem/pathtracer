#pragma once

#include <array>

namespace LinearAlgebra {
/**
 * @brief 3-dimensional vector
 *
 * @tparam T Type of the components of vector
 * @tparam ScalarT Scalar type for operations like addition. (Not the type of
 * field on which this vector is defined. Otherwise this would be same as T)
 */
template<typename T, typename ScalarT>
class Vec3Template
{
  public:
    /**
     * @brief Construct a zero-vector
     *
     */
    Vec3Template();

    /**
     * @brief Construct a new Vec 3 object with given components
     *
     * @param x
     * @param y
     * @param z
     */
    Vec3Template(T x, T y, T z);

    /**
     * @brief Calculate the norm (size) of this vector
     *
     * @return float
     */
    float norm();

    /**
     * @brief Calculate a unit vector with the same direction as this one.
     * Behavior is undefined if this is a zero-vector
     *
     * @return Vec3Template this vector divided by its norm
     */
    Vec3Template normalize();

    /**
     * @brief Divide each component by scalar
     *
     * @tparam ScalarT
     * @return Vec3Template
     */
    Vec3Template operator/(ScalarT);

    /**
     * @brief Multiply each component by scalar
     *
     * @tparam ScalarT
     * @return Vec3Template
     */
    Vec3Template operator*(ScalarT);

    /**
     * @brief Add a scalar to each component
     *
     * @tparam ScalarT
     * @return Vec3Template
     */
    Vec3Template operator+(ScalarT);

    /**
     * @brief Subtract a scalar from each component
     *
     * @tparam ScalarT
     * @return Vec3Template
     */
    Vec3Template operator-(ScalarT);

    /**
     * @brief Vector addition
     *
     * @return Vec3Template
     */
    Vec3Template operator+(Vec3Template);

    /**
     * @brief Vector subtraction
     *
     * @return Vec3Template
     */
    Vec3Template operator-(Vec3Template);

    /**
     * @brief Vector addition
     *
     * @return Vec3Template& A reference to this object
     */
    Vec3Template& operator+=(Vec3Template);

    /**
     * @brief Vector subtraction
     *
     * @return Vec3Template& A reference to this object
     */
    Vec3Template& operator-=(Vec3Template);

    T x, y, z;
};

using Vec3 = Vec3Template<float, float>;
using Vec3f = Vec3Template<float, float>;
using Vec3d = Vec3Template<double, double>;
using Vec3i = Vec3Template<int, float>;

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>::Vec3Template()
  : x(0)
  , y(0)
  , z(0)
{}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>::Vec3Template(T x, T y, T z)
  : x(x)
  , y(y)
  , z(z)
{}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator/(ScalarT s)
{
    return { x / s, y / s, z / s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator-(ScalarT s)
{
    return { x - s, y - s, z - s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator+(ScalarT s)
{
    return { x + s, y + s, z + s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator*(ScalarT s)
{
    return { x * s, y * s, z * s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator+(Vec3Template<T, ScalarT> other)
{
    return { x + other.x, y + other.y, z + other.z };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator-(Vec3Template<T, ScalarT> other)
{
    return { x - other.x, y - other.y, z - other.z };
}
} // namespace LinearAlgebra
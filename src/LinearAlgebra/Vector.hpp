#pragma once

#include <cmath>

namespace LinearAlgebra {
/**
 * @brief 3-dimensional vector
 *
 * @tparam T Stored type of the components of vector
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
     * @return T
     */
    T norm() const;

    /**
     * @brief Calculates the square of this vector's norm
     *
     * @return T norm of this vector squared
     */
    T squaredNorm() const;

    /**
     * @brief Calculate a unit vector with the same direction as this one.
     * Behavior is undefined if this is a zero-vector
     *
     * @return Vec3Template<T, ScalarT> this vector divided by its norm
     */
    Vec3Template<T, ScalarT> normalize() const;

    /**
     * @brief Divide each component by scalar
     *
     * @tparam ScalarT
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator/(ScalarT) const;

    /**
     * @brief Multiply each component by scalar
     *
     * @tparam ScalarT
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator*(ScalarT) const;

    /**
     * @brief Scalar multiplication, from the left (same as the member function)
     *
     * @return Vec3Template<T, ScalarT>
     */
    template<typename T2, typename ScalarT2>
    friend Vec3Template<T2, ScalarT2> operator*(ScalarT2,
                                                Vec3Template<T2, ScalarT2>);

    /**
     * @brief Add a scalar to each component
     *
     * @tparam ScalarT
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator+(ScalarT) const;

    /**
     * @brief Subtract a scalar from each component
     *
     * @tparam ScalarT
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator-(ScalarT) const;

    /**
     * @brief Vector addition
     *
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator+(const Vec3Template<T, ScalarT>&) const;

    /**
     * @brief Vector subtraction
     *
     * @return Vec3Template<T, ScalarT>
     */
    Vec3Template<T, ScalarT> operator-(const Vec3Template<T, ScalarT>&) const;

    /**
     * @brief Vector addition
     *
     * @return Vec3Template<T, ScalarT>& A reference to this object
     */
    Vec3Template<T, ScalarT>& operator+=(const Vec3Template<T, ScalarT>&);

    /**
     * @brief Vector subtraction
     *
     * @return Vec3Template<T, ScalarT>& A reference to this object
     */
    Vec3Template<T, ScalarT>& operator-=(const Vec3Template<T, ScalarT>&);

    /**
     * @brief Right-handed cross product
     *
     * @param other
     * @return Vec3Template<T, ScalarT> this X other
     */
    Vec3Template<T, ScalarT> cross(const Vec3Template<T, ScalarT>& other) const;

    /**
     * @brief Dot product
     *
     * @param other
     * @return ScalarT Sum of the components of component-wise multiplication
     */
    ScalarT dot(const Vec3Template<T, ScalarT>& other) const;

    /**
     * @brief Compares each element using ==. I am not sure if I should include
     * this as it may cause more problems than it solves.
     *
     * @param other
     * @return true All elements compare equal using ==
     * @return false Some elements are not equal
     */
    bool operator==(const Vec3Template<T, ScalarT>& other) const;

    /**
     * @brief Opposite of operator==
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator!=(const Vec3Template<T, ScalarT>& other) const;

    T x, y, z;

    using ComponentType = T;
    using ScalarType = ScalarT;
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
T
Vec3Template<T, ScalarT>::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

template<typename T, typename ScalarT>
T
Vec3Template<T, ScalarT>::squaredNorm() const
{
    return x * x + y * y + z * z;
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::normalize() const
{
    return *this / norm();
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator/(ScalarT s) const
{
    return { x / s, y / s, z / s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator-(ScalarT s) const
{
    return { x - s, y - s, z - s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator+(ScalarT s) const
{
    return { x + s, y + s, z + s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator*(ScalarT s) const
{
    return { x * s, y * s, z * s };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
operator*(ScalarT s, Vec3Template<T, ScalarT> vec)
{
    return vec * s;
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator+(const Vec3Template<T, ScalarT>& other) const
{
    return { x + other.x, y + other.y, z + other.z };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::operator-(const Vec3Template<T, ScalarT>& other) const
{
    return { x - other.x, y - other.y, z - other.z };
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>&
Vec3Template<T, ScalarT>::operator-=(const Vec3Template<T, ScalarT>& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>&
Vec3Template<T, ScalarT>::operator+=(const Vec3Template<T, ScalarT>& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T, typename ScalarT>
Vec3Template<T, ScalarT>
Vec3Template<T, ScalarT>::cross(const Vec3Template<T, ScalarT>& other) const
{
    return { y * other.z - z * other.y,
             z * other.x - x * other.z,
             x * other.y - y * other.x };
}

template<typename T, typename ScalarT>
ScalarT
Vec3Template<T, ScalarT>::dot(const Vec3Template<T, ScalarT>& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

template<typename T, typename ScalarT>
bool
Vec3Template<T, ScalarT>::operator==(
  const Vec3Template<T, ScalarT>& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

template<typename T, typename ScalarT>
bool
Vec3Template<T, ScalarT>::operator!=(
  const Vec3Template<T, ScalarT>& other) const
{
    return !(*this == other);
}
} // namespace LinearAlgebra
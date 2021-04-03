#pragma once

#include <initializer_list>

namespace LinearAlgebra {
template<typename T = float>
class Vec3
{
  public:
    /**
     * @brief Construct a zero-vector
     *
     */
    Vec3();

    /**
     * @brief Construct a new Vec 3 object with given components
     *
     * @param x
     * @param y
     * @param z
     */
    Vec3(T x, T y, T z);

    /**
     * @brief Construct a new Vec 3 object from an initializer list
     *
     * @param il Initializer list
     */
    Vec3(std::initializer_list<T> il);

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
     * @return Vec3 this vector divided by its norm
     */
    Vec3 normalize();

    /**
     * @brief Divide each component by scalar
     *
     * @tparam scalarT
     * @return Vec3
     */
    template<typename scalarT>
    Vec3 operator/(scalarT);

    /**
     * @brief Multiply each component by scalar
     *
     * @tparam scalarT
     * @return Vec3
     */
    template<typename scalarT>
    Vec3 operator*(scalarT);

    /**
     * @brief Add a scalar to each component
     *
     * @tparam scalarT
     * @return Vec3
     */
    template<typename scalarT>
    Vec3 operator+(scalarT);

    /**
     * @brief Subtract a scalar from each component
     *
     * @tparam scalarT
     * @return Vec3
     */
    template<typename scalarT>
    Vec3 operator-(scalarT);

    /**
     * @brief Vector addition
     *
     * @return Vec3
     */
    Vec3 operator+(Vec3);

    /**
     * @brief Vector subtraction
     *
     * @return Vec3
     */
    Vec3 operator-(Vec3);

    /**
     * @brief Vector addition
     *
     * @return Vec3& A reference to this object
     */
    Vec3& operator+=(Vec3);

    /**
     * @brief Vector subtraction
     *
     * @return Vec3& A reference to this object
     */
    Vec3& operator-=(Vec3);

    T x, y, z;
};

template<typename T>
Vec3<T>::Vec3()
  : x(0)
  , y(0)
  , z(0)
{}

template<typename T>
Vec3<T>::Vec3(T x, T y, T z)
  : x(y)
  , y(y)
  , z(z)
{}

template<typename T>
Vec3<T>::Vec3(std::initializer_list<T> il)
  : x(il[0])
  , y(il[1])
  , z(il[2])
{}

template<typename T>
template<typename scalarT>
Vec3<T>
Vec3<T>::operator/(scalarT s)
{
    return { x / s, y / s, z / s };
}

template<typename T>
template<typename scalarT>
Vec3<T>
Vec3<T>::operator-(scalarT s)
{
    return { x - s, y - s, z - s };
}

template<typename T>
template<typename scalarT>
Vec3<T>
Vec3<T>::operator+(scalarT s)
{
    return { x + s, y + s, z + s };
}

template<typename T>
template<typename scalarT>
Vec3<T>
Vec3<T>::operator*(scalarT s)
{
    return { x * s, y * s, z * s };
}
} // namespace LinearAlgebra
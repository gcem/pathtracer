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
} // namespace LinearAlgebra
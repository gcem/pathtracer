#include "Vector.hpp"

template <typename T = float>
class Mat3 {
    // creates an identity matrix
    Mat3();

    // takes columns of matrix as arguments
    Mat3(Vec3<T> col1, Vec3<T> col2, Vec3<T> col3);

    // @param il in row-major order (i.e. a11, a12, a13, a21, ...)
    Mat3(std::initializer_list<T> il);

    T determinant();

    // matrix multiplication
    // @returns this * other
    Mat3 operator*(Mat3<T> &other);

    // matrix-vector multiplication
    Vec3<T> operator*(Vec3<T> &vec);

    Vec3<T> col1, col2, col3;
};
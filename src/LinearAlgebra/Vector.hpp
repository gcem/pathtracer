template <typename T = float>
class Vec3 {
public:
    Vec3();
    Vec3(T, T, T);
    Vec3(std::initializer_list<T> il);

    float norm();
    Vec3 normalize();

    // divide each component by scalar
    template <typename scalarT>
    Vec3 operator/(scalarT);

    // multiply each component by scalar
    template <typename scalarT>
    Vec3 operator*(scalarT);

    // add scalar to each component
    template <typename scalarT>
    Vec3 operator+(scalarT);

    // subtract scalar from each component
    template <typename scalarT>
    Vec3 operator-(scalarT);

    Vec3 operator+(Vec3);
    Vec3 operator-(Vec3);

    // @returns a reference to this object
    Vec3 &operator+=(Vec3);

    // @returns a reference to this object
    Vec3 &operator-=(Vec3);

    T x, y, z;
};
#include "Triangle.hpp"
#include "Matrix.hpp"

namespace PathTracer {
Triangle::Triangle(const LinearAlgebra::Vec3& vertex1,
                   const LinearAlgebra::Vec3& vertex2,
                   const LinearAlgebra::Vec3& vertex3)
  : v1(vertex1)
  , v2(vertex2)
  , v3(vertex3)
{
    normal = (v2 - v1).cross(v3 - v2).normalize();
}

FloatT
Triangle::intersect(const Ray& ray) const
{
    /**
     * We solve the equation
     * origin + t * direction = v1 + beta * edge12 + gamma * edge13
     *
     * This is same as
     * t * direction - beta * edge12 - gamma * edge13 = v1 - origin
     *
     * [direction edge21 edge31] * (t, beta, gamma) = v1 - origin
     *
     */
    auto edge21 = v1 - v2;
    auto edge31 = v1 - v3;
    auto rhs = v1 - ray.origin;

    auto detA =
      LinearAlgebra::Mat3(ray.direction, edge21, edge31).determinant();
    // if detA is 0, then the triangle is degenerate. but I won't check this

    auto detT = LinearAlgebra::Mat3(rhs, edge21, edge31).determinant();
    auto t = detT / detA;

    if (t <= 0)
        return -1;

    auto detB = LinearAlgebra::Mat3(ray.direction, rhs, edge31).determinant();
    auto beta = detB / detA;

    if (beta < 0 || beta > 1)
        return -1;

    auto detC = LinearAlgebra::Mat3(ray.direction, edge21, rhs).determinant();
    auto gamma = detC / detA;

    if (gamma < 0 || beta + gamma > 1)
        return -1;

    return t;
}

LinearAlgebra::Vec3
Triangle::getNormal() const
{
    return normal;
}
}
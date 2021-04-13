#include "Sphere.hpp"

namespace Objects {
Sphere::Sphere(const LinearAlgebra::Vec3& center,
               FloatT radius,
               const Material& material)
  : Surface(material)
  , center(center)
  , radius(radius)
{}

FloatT
Sphere::intersect(const Ray& ray,
                  LinearAlgebra::Vec3& normalOut,
                  FloatT epsilon) const
{
    /**
     * Solve the equation
     * |origin + t * direction - center| = radius
     *
     * Denoting dot product by self with "^ 2":
     *
     * (t * direction + origin - center) ^ 2 = radius * radius
     *
     * t ^ 2 * direction ^ 2 + t * 2 * direction * (origin - center) + (origin
     * - center) ^ 2 - radius ^ 2 = 0
     *
     */

    // at^2 + bt + c = 0
    auto a = ray.direction.squaredNorm();
    auto b = 2 * ray.direction.dot(ray.origin - center);
    auto c = (ray.origin - center).squaredNorm() - radius * radius;

    auto delta = b * b - 4 * a * c;

    if (delta < 0)
        return -1;

    auto t = (-b - sqrt(delta)) / (2 * a);
    if (t <= 0)
        t = (-b + sqrt(delta)) / (2 * a);

    if (t <= 0)
        return -1;

    normalOut = (ray.origin + ray.direction * t - center).normalize();
    return t;
}

bool
Sphere::intersectsBefore(const Ray& ray, FloatT maxT, FloatT epsilon) const
{
    // see intersect() for an explanation of this calculation

    auto a = ray.direction.squaredNorm();
    auto b = 2 * ray.direction.dot(ray.origin - center);
    auto c = (ray.origin - center).squaredNorm() - radius * radius;

    auto delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    auto t = (-b - sqrt(delta)) / (2 * a);
    if (t <= 0)
        t = (-b + sqrt(delta)) / (2 * a);

    return t > 0 && t < maxT;
}
}
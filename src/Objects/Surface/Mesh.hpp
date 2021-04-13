/**
 * @file Mesh.hpp
 * @author Cem Gundogdu
 * @brief Mesh of triangles
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Config.hpp"
#include "Ray.hpp"
#include "Surface.hpp"
#include "Triangle.hpp"
#include <vector>

namespace Objects {
/**
 * @brief Mesh of triangles, all having the same material
 *
 */
class Mesh : public Surface
{
public:
    /**
     * @brief Construct a new Mesh object with given vertices
     *
     * Takes a vertex array, which may also include vertices that are not in
     * this mesh. Also takes the vertex indices of each triangle (Vertex vector
     * is 0-indexed as usual). Constructs a triangle mesh.
     *
     * @param vertices Vector of vertex positions
     * @param indices An index vector. Groups of three indices corresponds to a
     * triangle
     * @param material
     */
    Mesh(const std::vector<LinearAlgebra::Vec3>& vertices,
         const std::vector<int>& indices,
         const Material& material);

    /**
     * @brief Finds the intersection of given ray with this mesh.
     *
     * If there is an intersection, returns the t value and sets normalOut to
     * the normal of the intersecting triangle. Otherwise returns -1.
     *
     * If return value is not -1, then it is a positive number t such that
     * ray.origin + t * ray.direction is on one of the triangles in this mesh.
     * Returns the least positive number with this property.
     *
     * @param ray
     * @param normalOut If return value is not -1, then this is set to the
     * surface normal at intersection point. Otherwise unmodified.
     * @param epsilon Positive values make the triangles a bit larger than it
     * is. Used for avoiding floating-point issues.
     * @return FloatT t for the closest intersection with ray, -1 if there is no
     * intersection.
     */
    FloatT intersect(const Ray& ray,
                     LinearAlgebra::Vec3& normalOut,
                     FloatT epsilon = 0) const override;

    /**
     * @brief Finds if ray intersects this mesh with a t value lower than
     * maxT
     *
     * Looks for an intersection with t in range (0, maxT)
     *
     * @param ray
     * @param maxT Upper limit of t value for intersection test to succeed
     * (exclusive)
     * @return true There is a triangle closer than t
     * @return false There is no such triangle
     */
    bool intersectsBefore(const Ray& ray,
                          FloatT maxT,
                          FloatT epsilon = 0) const override;

protected:
    /**
     * @brief Triangles in this mesh
     *
     */
    std::vector<Triangle> triangles;
};
}
#include "Mesh.hpp"
#include <cmath>
#include <limits>

namespace PathTracer {
Mesh::Mesh(const std::vector<LinearAlgebra::Vec3>& vertices,
           const std::vector<int>& indices,
           const Material& material)
  : Surface(material)
{
    triangles.reserve(indices.size() / 3);
    for (int i = 0; i < indices.size(); i += 3)
        triangles.push_back({ vertices[indices[i]],
                              vertices[indices[i + 1]],
                              vertices[indices[i + 2]] });
}

FloatT
Mesh::intersect(const Ray& ray, LinearAlgebra::Vec3& normalOut) const
{
    FloatT minT = std::numeric_limits<FloatT>::infinity();
    for (auto& triangle : triangles) {
        auto t = triangle.intersect(ray);
        if (t != -1 && t < minT) {
            minT = t;
            normalOut = triangle.getNormal();
        }
    }
    return minT < std::numeric_limits<FloatT>::infinity() ? minT : -1;
}
}
#include "Mesh.hpp"
#include <cmath>
#include <limits>

namespace Objects {
Mesh::Mesh(const std::vector<LinearAlgebra::Vec3>& vertices,
           const std::vector<int>& indices,
           const Material& material,
           std::unique_ptr<AccelerationStructures::AccelerationStructure>
             accelerationStructure)
  : Surface(material)
  , acc(std::move(accelerationStructure))
{
    std::vector<Triangle> triangles;
    triangles.reserve(indices.size() / 3);
    for (int i = 0; i < indices.size(); i += 3)
        triangles.push_back({ vertices[indices[i]],
                              vertices[indices[i + 1]],
                              vertices[indices[i + 2]] });
    acc->build(std::move(triangles));
}

FloatT
Mesh::intersect(const Ray& ray, LinearAlgebra::Vec3& normalOut) const
{
    return acc->intersect(ray, normalOut);
}
}
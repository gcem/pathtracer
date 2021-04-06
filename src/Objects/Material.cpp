#include "Material.hpp"
namespace PathTracer {
Material::Material()
  : Material({ 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 })
{}

Material::Material(const LinearAlgebra::Vec3& ambient,
                   const LinearAlgebra::Vec3& diffuse,
                   const LinearAlgebra::Vec3& specular)
  : ambient(ambient)
  , diffuse(diffuse)
  , specular(specular)
{}
}
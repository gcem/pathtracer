#include "Material.hpp"
namespace Objects {
Material::Material()
  : Material({ 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 }, 1)
{}

Material::Material(const LinearAlgebra::Vec3& ambient,
                   const LinearAlgebra::Vec3& diffuse,
                   const LinearAlgebra::Vec3& specular,
                   FloatT phongExponent)
  : ambient(ambient)
  , diffuse(diffuse)
  , specular(specular)
  , phongExponent(phongExponent)
{}
}
#include "Material.hpp"
namespace Objects {
Material::Material()
  : Material({ 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 }, 1)
{}

Material::Material(const LinearAlgebra::Vec3& ambient,
                   const LinearAlgebra::Vec3& diffuse,
                   const LinearAlgebra::Vec3& specular,
                   FloatT phongExponent,
                   Type type,
                   const LinearAlgebra::Vec3& mirrorReflectance,
                   const LinearAlgebra::Vec3& absorptionCoefficient,
                   FloatT refractionIndex,
                   FloatT absorptionIndex)
  : type(type)
  , ambient(ambient)
  , diffuse(diffuse)
  , specular(specular)
  , phongExponent(phongExponent)
  , mirrorReflectance(mirrorReflectance)
  , absorptionCoefficient(absorptionCoefficient)
  , refractionIndex(refractionIndex)
  , absorptionIndex(absorptionIndex)
{}
}
/**
 * @file Material.hpp
 * @author Cem Gundogdu
 * @brief
 * @version 1.0
 * @date 2021-04-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Vector.hpp"

namespace Objects {
/**
 * @brief Holds the properties of a material
 *
 * @todo Maybe I should create separate classes for different material types
 */
class Material
{
public:
    enum class Type
    {
        Default,
        Dielectric,
        Conductor,
        Mirror
    };

    /**
     * @brief Construct a default Material object
     *
     * Sets all colors to 1.
     *
     */
    Material();

    /**
     * @brief Construct a Material object with given properties
     *
     * Default values don't make much sense. Set values explicitly if you will
     * ever use them.
     *
     * @param ambient
     * @param diffuse
     * @param specular
     * @param phongExponent
     * @param type
     * @param mirrorReflectance
     * @param absorptionCoefficient
     * @param refractionIndex
     * @param absorptionIndex
     */
    Material(const LinearAlgebra::Vec3& ambient,
             const LinearAlgebra::Vec3& diffuse,
             const LinearAlgebra::Vec3& specular,
             FloatT phongExponent,
             Type type = Type::Default,
             const LinearAlgebra::Vec3& mirrorReflectance = {},
             const LinearAlgebra::Vec3& absorptionCoefficient = {},
             FloatT refractionIndex = 1,
             FloatT absorptionIndex = 0);

    /**
     * @brief Material type (dielectric, conductor etc.)
     *
     */
    Type type;

    /**
     * @brief RGB values of ambient color
     *
     */
    LinearAlgebra::Vec3 ambient;

    /**
     * @brief RGB values of diffuse color
     *
     */
    LinearAlgebra::Vec3 diffuse;

    /**
     * @brief RGB values of specular color
     *
     */
    LinearAlgebra::Vec3 specular;

    /**
     * @brief Phong exponent
     *
     * Determines how shiny the surface looks. If exponent is higher, phong
     * reflectance decays faster with distance to peak point.
     *
     */
    FloatT phongExponent;

    /**
     * @brief Mirror reflectance coefficients for RGB colors
     *
     */
    LinearAlgebra::Vec3 mirrorReflectance;

    /**
     * @brief Absorption coefficient for dielectric materials
     *
     * Used to attenuate RGB components of the ray as it travels inside the
     * dielectric.
     *
     */
    LinearAlgebra::Vec3 absorptionCoefficient;

    /**
     * @brief Refraction index as in physics
     *
     */
    FloatT refractionIndex;

    /**
     * @brief Absorption index for conductors
     *
     */
    FloatT absorptionIndex;
};
}
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

namespace PathTracer {
/**
 * @brief Holds the properties of a material
 *
 */
class Material
{
public:
    /**
     * @brief Construct a default Material object
     *
     * Sets all colors to 1.
     *
     */
    Material();

    /**
     * @brief Construct a Material object with given colors
     *
     * @param ambient
     * @param diffuse
     * @param specular
     */
    Material(const LinearAlgebra::Vec3& ambient,
             const LinearAlgebra::Vec3& diffuse,
             const LinearAlgebra::Vec3& specular);

    /**
     * @brief RGB values of ambient color
     *
     */
    const LinearAlgebra::Vec3 ambient;

    /**
     * @brief RGB values of diffuse color
     *
     */
    const LinearAlgebra::Vec3 diffuse;

    /**
     * @brief RGB values of specular color
     *
     */
    const LinearAlgebra::Vec3 specular;
};
}
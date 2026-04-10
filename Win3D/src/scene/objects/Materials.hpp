#pragma once

#include "util/Util.hpp"
#include <variant>

namespace Mat {
    // * ------------------------------------------- [ MATERIALS ] ------------------------------------------- * //

    struct DisneyBSDF {
        double roughness;
        double subsurface;
        double sheen;
        double sheenTint;
        double anisotropic;
        double metallic;
        double specular;
        double specularTransmission;
        double specularTint;
        double clearcoat;
        double clearcoatGloss;
        double eta;
    } typedef DisneyBSDF;

    struct DisneyDiffuse {
        double roughness;
        double subsurface;
    
    } typedef DisneyDiffuse;
    
    struct DisneyMetal {
        double roughness;
        double anisotropic;
    
    } typedef DisneyMetal;
    
    struct DisneyClearcoat {
        Colour clearcoatGloss;
    } typedef DisneyClearcoat;
    
    struct DisneyGlass {
        Colour baseColour;
        double roughness;
        double anisotropic;
        double eta;
    } typedef DisneyGlass;
    
    struct DisneySheen {
        Colour baseColour;
        double sheenTint;
    } typedef DisneySheen;

    // * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //
    
    typedef std::variant<DisneyBSDF, DisneyDiffuse, DisneyMetal, DisneyClearcoat, DisneyGlass, DisneySheen> Material;
    
    struct evaluate {
        const Vector& in;
        const Vector& out;
        const Vector& normal;
        const Colour& baseColour;
    
        Colour operator()(const DisneyBSDF& material) const;
        Colour operator()(const DisneyDiffuse& material) const;
        Colour operator()(const DisneyMetal& material) const;
        Colour operator()(const DisneyClearcoat& material) const;
        Colour operator()(const DisneyGlass& material) const;
        Colour operator()(const DisneySheen& material) const;
    };

    Colour eval(const Material& mat, Vector in, Vector out, Vector normal, Colour colour);
}

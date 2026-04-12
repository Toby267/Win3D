#pragma once

#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"
#include <variant>
#include <vector>

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

    // * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //
    
    typedef std::variant<DisneyBSDF, DisneyDiffuse> Material;
    
    struct evaluateBxDF {
        const Vector& in;       // or light or L
        const Vector& out;      // or camera or V
        const Vector& normal;   // or N
        const Vector& X;        // orthoganol basis vectors
        const Vector& Y;        // orthoganol basis vectors
        const Colour& baseColour;
    
        Colour operator()(const DisneyBSDF& material) const;
        Colour operator()(const DisneyDiffuse& material) const;
    };

    Colour eval(const Material& mat, Vector in, Vector out, Vector normal, Vector X, Vector Y, Colour normalisedMatColour, Colour normalisedlightColour);

    Colour evaluateLights(const Material& mat, Vector out, Vector normal, Vector X, Vector Y, Colour normalisedMatColour, Vector position, std::vector<PointLight> lights);
}

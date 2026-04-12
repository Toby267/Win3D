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
    
    // struct DisneyClearcoat {
    //     Colour clearcoatGloss;
    // } typedef DisneyClearcoat;
    
    // struct DisneyGlass {
    //     Colour baseColour;
    //     double roughness;
    //     double anisotropic;
    //     double eta;
    // } typedef DisneyGlass;
    
    // struct DisneySheen {
    //     Colour baseColour;
    //     double sheenTint;
    // } typedef DisneySheen;

    // * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //
    
    typedef std::variant<DisneyBSDF, DisneyDiffuse, DisneyMetal/*, DisneyClearcoat, DisneyGlass, DisneySheen*/> Material;
    
    struct evaluateBxDF {
        const Vector& in;       // or light or L
        const Vector& out;      // or camera or V
        const Vector& normal;   // or N
        const Vector& X;        // orthoganol basis vectors
        const Vector& Y;        // orthoganol basis vectors
        /* need to find the rest of the values that are inputs to brdfs. they are in the brdfs from scratch file, and are: N, V, L, H, R, T, v, l, phi v, phi l */
        /* actually in the implementation on github, only L, V, N, X, Y is used */
        /* so all i have to do is find X and Y */
        const Colour& baseColour;
    
        Colour operator()(const DisneyBSDF& material) const;
        Colour operator()(const DisneyDiffuse& material) const;
        Colour operator()(const DisneyMetal& material) const;
        // Colour operator()(const DisneyClearcoat& material) const;
        // Colour operator()(const DisneyGlass& material) const;
        // Colour operator()(const DisneySheen& material) const;
    };

    Colour eval(const Material& mat, Vector in, Vector out, Vector normal, Vector X, Vector Y, Colour normalisedMatColour, Colour normalisedlightColour);

    Colour evaluateLights(const Material& mat, Vector out, Vector normal, Vector X, Vector Y, Colour normalisedMatColour, Vector position, std::vector<PointLight> lights);
}

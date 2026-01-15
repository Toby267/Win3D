#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <variant>

// in doom, brdf calculations were only done for triangle vertices, then the colours of the triangle were interpolated

// todo:
// perspective correct interpolation using uv coordiantes
// get brdfs working in the ray tracer per fragment, using the above to interpolate the base colour
    // if too slow, get it working per vertex and interpoalte - will need to increase the number of triangles

// key decision: ray casting (per vertex) -> rasterization (with perspective correct interpolation)
//           or: rasterization -> ray casting (per fragment with perspective correct interpolation) - this one, is faster for single thread rendering

// i think, for efficiency, i need to do a version where only certain key objects use ray casting at all, then rest only do rasterization
    // the ray casting for all vertices then rasterization to interpolate method is too slow for me, as i can't do the trick he did with only having 320 rays
    // therefore i will do a raster pass with perspective correct interpolation, on a data structure that only holds raster objects
    // then a ray tracing pass on a bvh only containing ray casting objects (with per fragment brdf calculation - or per vertex with perspective correct interpoaltion if too slow)
        // this way there are definitely efficiencies to be made since only subsets of the screen will need rays to be generated.


// Thursday's job:
    // 1 - disney diffuse working with single light source
    // 2 - some of the other brdfs done
// Friday's job:
    // 1 - disney bsdf done
    // 2 - visitor interface working with multiple light sources

namespace Mat {
    struct DisneyDiffuse {
        double roughness;
        double subsurface;
    
        DisneyDiffuse(double roughness, double subsurface);
    } typedef DisneyDiffuse;
    
    struct DisneyMetal {
        double roughness;
        double anisotropic;
    
    } typedef DisneyMetal;
    
    typedef std::variant<DisneyDiffuse, DisneyMetal> Material;
    
    struct visitor {
        const Vector& in;
        const Vector& out;
        const Vector& normal;
        const Colour& colour;
    
        Colour operator()(const DisneyDiffuse& material) const;
        Colour operator()(const DisneyMetal& material) const;
    };

    Colour eval(const Material& mat, Vector in, Vector out, Vector normal, Colour c0, Colour c1, Colour c2, float u, float v);
}

// struct DisneyBSDF {
//     Colour baseColour;
//     double roughness;
//     double subsurface;
//     double sheen;
//     double sheenTint;
//     double anisotropic;
//     double metallic;
//     double specular;
//     double specularTransmission;
//     double specularTint;
//     double clearcoat;
//     double clearcoatGloss;
//     double eta;
// } typedef DisneyBSDF;

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
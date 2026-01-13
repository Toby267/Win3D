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


// Wednesday's job:
    // 1 - ray casting shading with barycentric coordiantes
    // 2 - visitor interface for brdf's
// Thursday's job:
    // 1 - disney diffuse working with single light source
    // 2 - some of the other brdfs done
// Friday's job:
    // 1 - disney bsdf done
    // 2 - visitor interface working with multiple light sources

namespace Materials {
    struct DisneyDiffuse {
        Colour baseColour;
        double roughness;
        double subsurface;
    
        DisneyDiffuse(Colour colour, double roughness, double subsurface);
        Colour eval(Vector in, Vector out, Vector normal);
    } typedef DisneyDiffuse;
    
    struct DisneyMetal {
        Colour baseColour;
        double roughness;
        double anisotropic;
    
        Colour eval(Vector in, Vector out, Vector normal);
    } typedef DisneyMetal;
    
    typedef std::variant<DisneyDiffuse, DisneyMetal> Shader;
    
    struct ShaderVisitor {
        Colour eval(DisneyDiffuse& mat, Vector in, Vector out, Vector normal) {return mat.eval(in, out, normal);}
        Colour eval(DisneyMetal& mat, Vector in, Vector out, Vector normal) {return mat.eval(in, out, normal);}
    } typedef ShaderVisitor;
    
    extern ShaderVisitor visitor;
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

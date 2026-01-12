#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <variant>

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

typedef std::variant<DisneyDiffuse, DisneyMetal> Material;

struct MatVisitor {
    Colour eval(DisneyDiffuse& mat, Vector in, Vector out, Vector normal) {return mat.eval(in, out, normal);}
    Colour eval(DisneyMetal& mat, Vector in, Vector out, Vector normal) {return mat.eval(in, out, normal);}
} typedef MatVisitor;

extern MatVisitor MaterialVisitor;



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

#pragma once

#include "util/Colour.hpp"

struct DisneyBSDF {
    Colour baseColour;
    float roughness;
    float subsurface;
    float sheen;
    float sheenTint;
    float anistropic;
    float metallic;
    float specular;
    float specularTint;
    float clearcoat;
    float clearcoatGloss;
} typedef DisneyBSDF;

struct BlenderBSDF {
    Colour baseColour;
    float metallic;
    float roughness;
    float IOR;
    float alpha;
} typedef BlenderBSDF;
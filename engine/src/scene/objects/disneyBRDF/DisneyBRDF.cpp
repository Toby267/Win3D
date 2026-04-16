#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include <algorithm>
#include <cmath>
#include <numbers>

// the following is licensed from: https://github.com/wdas/brdf/blob/main/src/brdfs/disney.brdf
// various modifications have been made to make it congruent with the rest of the codebase

// Copyright Disney Enterprises, Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License
// and the following modification to it: Section 6 Trademarks.
// deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the
// trade names, trademarks, service marks, or product names of the
// Licensor and its affiliates, except as required for reproducing
// the content of the NOTICE file.
//
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#define mix(a, b, w) (a * (1.0-w) + b * w)

double SchlickFresnel(double u) {
    float m = std::clamp(1.0-u, 0.0, 1.0);
    return std::pow(m, 5);
}

double GTR1(double NdotH, double a) {
    if (a >= 1) return std::numbers::inv_pi;
    double a2 = a*a;
    double t = 1 + (a2-1)*NdotH*NdotH;
    return (a2-1) / (std::numbers::pi*std::log(a2)*t);
}

double GTR2(double NdotH, double a) {
    double a2 = a*a;
    double t = 1 + (a2-1)*NdotH*NdotH;
    return (a2-1) / (std::numbers::pi*t*t);
}

double GTR2_aniso(double NdotH, double HdotX, double HdotY, double ax, double ay) {
    double x = HdotX/ax, x2 = x*x;
    double y = HdotY/ay, y2 = y*y;

    double factor = x2 + y2 + NdotH*NdotH;
    
    return 1 / (std::numbers::pi * ax*ay * factor * factor);
}

double smithG_GGX(double NdotV, double alphaG) {
    double a = alphaG*alphaG;
    double b = NdotV*NdotV;
    return 1 / (NdotV + std::sqrt(a + b - a*b));
}

double smithG_GGX_aniso(double NdotV, double vDotX, double VdotY, double ax, double ay) {
    double x = vDotX*ax, x2 = x*x;
    double y = VdotY*ay, y2 = y*y;
    double n2 = NdotV*NdotV;
    
    return 1 / (NdotV + std::sqrt( x2 + y2 + n2 ));
}

Vector mon2lin(Colour x) {
    return Vector(std::pow(x.r(), 2.2), std::pow(x.g(), 2.2), std::pow(x.b(), 2.2));
}

Colour Mat::evaluateBxDF::operator()(const DisneyBSDF& mat) const {
    Vector L = in, V = out, N = normal;

    double NdotL = Vector::dotProduct(N, L);
    double NdotV = Vector::dotProduct(N, V);
    if (NdotL < 0 || NdotV < 0) return Colour(0.0, 0.0, 0.0, 0.0);

    Vector H = L+V;
    H = H.normalise();
    double NdotH = Vector::dotProduct(N, H);
    double LdotH = Vector::dotProduct(L, H);

    Vector Cdlin = mon2lin(baseColour);
    double Cdlum = 0.3*Cdlin[0] + 0.6*Cdlin[1] + 0.1*Cdlin[2];

    Vector Ctint = Cdlum > 0 ? Cdlin/Cdlum : Vector(1, 1, 1);
    Vector Cspec0 = mix(mix(Vector(1, 1, 1), Ctint, mat.specularTint) * mat.specular * 0.08, Cdlin, mat.metallic);
    Vector Csheen = mix(Vector(1, 1, 1), Ctint, mat.sheenTint);

    double FL = SchlickFresnel(NdotL), FV = SchlickFresnel(NdotV);
    double Fd90 = 0.5 + 2 * LdotH*LdotH * mat.roughness;
    double Fd = mix(1.0, Fd90, FL) * mix(1.0, Fd90, FV);

    double Fss90 = LdotH*LdotH*mat.roughness;
    double Fss = mix(1.0, Fss90, FL) * mix(1.0, Fss90, FV);
    double ss = 1.25 * (Fss * (1 / (NdotL + NdotV) - 0.5) + 0.5);

    double aspect = std::sqrt(mat.anisotropic*0.9);
    double ax = std::max(0.001, (mat.roughness*mat.roughness) / aspect);
    double ay = std::max(0.001, (mat.roughness*mat.roughness) * aspect);
    double Ds = GTR2_aniso(NdotH, Vector::dotProduct(H, X), Vector::dotProduct(H, Y), ax, ay);
    double FH = SchlickFresnel(LdotH);
    Vector Fs = mix(Cspec0, Vector(1, 1, 1), FH);
    double Gs = smithG_GGX_aniso(NdotL, Vector::dotProduct(L, X), Vector::dotProduct(L, Y), ax, ay) *
                smithG_GGX_aniso(NdotV, Vector::dotProduct(V, X), Vector::dotProduct(V, Y), ax, ay);

    Vector Fsheen = Csheen * FH * mat.sheen;

    double Dr = GTR1(NdotH, mix(0.1, 0.001, mat.clearcoatGloss));
    double Fr = mix(0.04, 1.0, FH);
    double Gr = smithG_GGX(NdotL, 0.25) * smithG_GGX(NdotV, 0.25);

    Vector retval = (Cdlin * std::numbers::inv_pi * mix(Fd, ss, mat.subsurface) + Fsheen)
                    * (1-mat.metallic)
                    + Fs*Gs*Ds + 0.25*mat.clearcoat*Gr*Fr*Dr;

    return Colour(retval[0], retval[1], retval[2]);
}

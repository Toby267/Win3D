#include "util/Vector.hpp"

#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------- [ CONSTRUCTORS/DESCTUCTOR/RULE OF 5 ] ------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector::Vector(int length) : length(length) {}
Vector::Vector(double x, double y) : length(2), vect(x, y, 0, 0) {}
Vector::Vector(double x, double y, double z) : length(3), vect(x, y, z, 0) {}
Vector::Vector(double x, double y, double z, double w) : length(4), vect(x, y, z, w) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::x() {
    return vect[0];
}
double& Vector::y(){
    return vect[1];
}
double& Vector::z(){
    return vect[2];
}
double& Vector::w() {
    return vect[3];
}

const double& Vector::x() const {
    return vect[0];
}
const double& Vector::y() const {
    return vect[1];
}
const double& Vector::z() const {
    return vect[2];
}
const double& Vector::w() const {
    return vect[3];
}

int Vector::getLength() const {
    return length;
}
double Vector::magnitude() const {
    double retVal = 0;

    for(int i = 0; i < length; i++)
        retVal += vect[i] * vect[i];

    return std::sqrt(retVal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector Vector::normalise() {
    double mag = magnitude();

    for (int i = 0; i < length; i++)
        vect[i] /= mag;

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::operator[](int i) {
    if (i >= length || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Vector or Matrix"));
    
    return vect[i];
}
const double& Vector::operator[](int i) const {
    if (i >= length || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Vector or Matrix"));
    
    return vect[i];
}

Vector Vector::operator*(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] * other;

    return vector;
}
Vector Vector::operator/(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] / other;

    return vector;
}
Vector Vector::operator+(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] + other;

    return vector;
}
Vector Vector::operator-(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] - other;

    return vector;
}

Vector Vector::operator*(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] * other[i];

    return vector;
}
Vector Vector::operator/(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] / other[i];

    return vector;
}
Vector Vector::operator+(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] + other[i];

    return vector;
}
Vector Vector::operator-(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = vect[i] - other[i];

    return vector;
}

Vector Vector::operator+() const {
    Vector vector(length);

    for (int i = 0; i < length; i++)
        vector[i] = +vect[i];

    return vector;
}
Vector Vector::operator-() const {
    Vector vector(length);

    for (int i = 0; i < length; i++)
        vector[i] = -vect[i];

    return vector;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v[0];

    for (int i = 1; i < v.length; i++)
        os << ", " << v[i];
    os << ")";

    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aka vector product
Vector Vector::crossProduct(const Vector& lhs, const Vector& rhs) {
    //
    //  | a |   | d |   |  (bf - ce) |    | (bf - ce) |
    //  | b | x | e | = | -(af - cd) | or | (cd - af) |
    //  | c |   | f |   |  (ae - bd) |    | (ae - bd) |
    //
    Vector vector(lhs.length);
    vector[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    vector[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    vector[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return vector;
}
double Vector::dotProduct(const Vector& lhs, const Vector& rhs) {
    double retVal = 0;
    
    for (int i = 0; i < lhs.length; i++)
        retVal += (lhs[i] * rhs[i]);

    return retVal;
}

Vector Vector::unitNormal(const Vector& lhs, const Vector& rhs) {
    Vector retVal = crossProduct(lhs, rhs);
    return retVal / retVal.magnitude();
}
double Vector::cosAngle(const Vector& lhs, const Vector& rhs) {
    return dotProduct(lhs, rhs) / (lhs.magnitude() * rhs.magnitude());
}

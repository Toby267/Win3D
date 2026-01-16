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
Vector::Vector(double x, double y) : length(2), data(x, y, 0, 0) {}
Vector::Vector(double x, double y, double z) : length(3), data(x, y, z, 0) {}
Vector::Vector(double x, double y, double z, double w) : length(4), data(x, y, z, w) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::x() {
    return data[0];
}
double& Vector::y(){
    return data[1];
}
double& Vector::z(){
    return data[2];
}
double& Vector::w() {
    return data[3];
}

const double& Vector::x() const {
    return data[0];
}
const double& Vector::y() const {
    return data[1];
}
const double& Vector::z() const {
    return data[2];
}
const double& Vector::w() const {
    return data[3];
}

int Vector::getLength() const {
    return length;
}
double Vector::magnitude() const {
    double retVal = 0;

    for(int i = 0; i < length; i++)
        retVal += data[i] * data[i];

    return std::sqrt(retVal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector Vector::normalise() {
    double mag = magnitude();

    for (int i = 0; i < length; i++)
        data[i] /= mag;

    return *this;
}

void Vector::toVec3() {
    length = 3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::operator[](int i) {
    if (i >= length || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Vector or Matrix"));
    
    return data[i];
}
const double& Vector::operator[](int i) const {
    if (i >= length || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Vector or Matrix"));
    
    return data[i];
}

Vector Vector::operator*(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] * other;

    return vector;
}
Vector Vector::operator/(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] / other;

    return vector;
}
Vector Vector::operator+(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] + other;

    return vector;
}
Vector Vector::operator-(double other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] - other;

    return vector;
}

Vector Vector::operator*(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] * other[i];

    return vector;
}
Vector Vector::operator/(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] / other[i];

    return vector;
}
Vector Vector::operator+(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] + other[i];

    return vector;
}
Vector Vector::operator-(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = data[i] - other[i];

    return vector;
}

Vector Vector::operator+() const {
    Vector vector(length);

    for (int i = 0; i < length; i++)
        vector[i] = +data[i];

    return vector;
}
Vector Vector::operator-() const {
    Vector vector(length);

    for (int i = 0; i < length; i++)
        vector[i] = -data[i];

    return vector;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << "(" << vector[0];

    for (int i = 1; i < vector.length; i++)
        os << ", " << vector[i];
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

//assumes the vectors origin is the world origin
Vector Vector::unitNormal(const Vector& lhs, const Vector& rhs) {
    Vector retVal = crossProduct(lhs, rhs);
    return retVal / retVal.magnitude();
}
double Vector::cosAngle(const Vector& lhs, const Vector& rhs) {
    return dotProduct(lhs, rhs) / (lhs.magnitude() * rhs.magnitude());
}

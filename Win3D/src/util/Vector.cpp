#include "util/Vector.hpp"

#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector::Vector(int length) {
    _length = length;
    v = new double[_length] {0};
}
Vector::Vector(int length, double a[]){
    _length = length;
    v = new double[_length];

    for (int i = 0; i < _length; i++)
        v[i] = a[i];
}
Vector::Vector(double a, double b) {
    _length = 2;
    v = new double[_length];
    v[0] = a;
    v[1] = b;
}
Vector::Vector(double a, double b, double c) {
    _length = 3;
    v = new double[_length];
    v[0] = a;
    v[1] = b;
    v[2] = c;
}
Vector::Vector(double a, double b, double c, double d) {
    _length = 4;
    v = new double[_length];
    v[0] = a;
    v[1] = b;
    v[2] = c;
    v[3] = d;
}
Vector::~Vector() {
    delete[] v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Vector::x() {
    return v[0];
}
double Vector::y() {
    return v[1];
}
double Vector::z() {
    return v[2];
}
double Vector::w() {
    return v[3];
}

int Vector::length() {
    return _length;
}
double Vector::magnitude() {
    double retVal = 0;

    for(int i = 0; i < _length; i++)
        retVal += v[i] * v[i];

    return std::sqrt(retVal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::operator[](int i) const {
    if (i >= _length || i < 0)
        throw std::out_of_range("Index out of range of vector");
    
    return v[i];
}
Vector Vector::operator/(const double& other) const {
    Vector vector(_length);
    
    for (int i = 0; i < _length; i++)
        vector[i] = v[i] / other;

    return vector;
}
Vector Vector::operator*(const double& other) const {
    Vector vector(_length);
    
    for (int i = 0; i < _length; i++)
        vector[i] = v[i] * other;

    return vector;
}
Vector Vector::operator*(const Vector& other) const {
    Vector vector(_length);
    
    for (int i = 0; i < _length; i++)
        vector[i] = v[i] * other[i];

    return vector;
}
Vector Vector::operator+(const Vector& other) const {
    Vector vector(_length);
    
    for (int i = 0; i < _length; i++)
        vector[i] = v[i] + other[i];

    return vector;
}
Vector Vector::operator-(const Vector& other) const {
    Vector vector(_length);
    
    for (int i = 0; i < _length; i++)
        vector[i] = v[i] - other[i];

    return vector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aka vector product
Vector Vector::crossProduct(Vector lhs, Vector rhs) {
    //
    //  | a |   | d |   |  (bf - ce) |    | (bf - ce) |
    //  | b | x | e | = | -(af - cd) | or | (cd - af) |
    //  | c |   | f |   |  (ae - bd) |    | (ae - bd) |
    //

    Vector vector(lhs.length());
    vector[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    vector[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    vector[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return vector;
}
double Vector::dotProduct(Vector lhs, Vector rhs) {
    double retVal = 0;
    
    for (int i = 0; i < lhs.length(); i++)
        retVal += (lhs[i] * rhs[i]);

    return retVal;
}

Vector Vector::unitNormal(Vector lhs, Vector rhs, Vector origin) {
    Vector retVal = crossProduct((lhs - origin), (rhs - origin));
    return retVal / retVal.magnitude();
}
double Vector::cosAngle(Vector lhs, Vector rhs, Vector origin) {
    Vector lhsPrime = lhs-origin, rhsPrime = rhs-origin;
    return dotProduct(lhsPrime, rhsPrime) / (lhsPrime.magnitude() * rhsPrime.magnitude());
}


std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v[0];

    for (int i = 1; i < v._length; i++)
        os << ", " << v[i];
    os << ")";

    return os;
}

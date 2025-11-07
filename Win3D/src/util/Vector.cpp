#include "util/Vector.hpp"

#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------- [ CONSTRUCTORS/DESCTUCTOR/RULE OF 5 ] ------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector::Vector() {
    length = 0;
    v = nullptr;
}
Vector::Vector(int _length) {
    this->length = _length;
    v = new double[length] {0};
}
Vector::Vector(int _length, double a[]){
    this->length = _length;
    v = new double[length];

    //TODO: test this change
    memcpy(v, a, sizeof(double)*length);
    // for (int i = 0; i < _length; i++)
        // v[i] = a[i];
}
Vector::Vector(double a, double b) {
    length = 2;
    v = new double[length];
    v[0] = a;
    v[1] = b;
}
Vector::Vector(double a, double b, double c) {
    length = 3;
    v = new double[length];
    v[0] = a;
    v[1] = b;
    v[2] = c;
}
Vector::Vector(double a, double b, double c, double d) {
    length = 4;
    v = new double[length];
    v[0] = a;
    v[1] = b;
    v[2] = c;
    v[3] = d;
}

//copy constructor
Vector::Vector(const Vector& other) {
    length = other.length;
    v = new double[length];
    memcpy(v, other.v, sizeof(double)*length);
}
//copy assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (v) delete[] v;
    
        length = other.length;
        v = new double[length];
        memcpy(v, other.v, sizeof(double)*length);
    }

    return *this;
}
//move constructor
Vector::Vector(Vector&& other) noexcept {
    length = other.length;
    v = other.v;

    other.length = 0;
    other.v = nullptr;
}
//move assignment operator
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        if (v) delete[] v;
    
        length = other.length;
        v = other.v;
        
        other.length = 0;
        other.v = nullptr;
    }

    return *this;
}
//destructor
Vector::~Vector() {
    if (v) delete[] v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::x() {
    return v[0];
}
double& Vector::y() {
    return v[1];
}
double& Vector::z() {
    return v[2];
}
double& Vector::w() {
    return v[3];
}

int Vector::getLength() const {
    return length;
}
double Vector::magnitude() const {
    double retVal = 0;

    for(int i = 0; i < length; i++)
        retVal += v[i] * v[i];

    return std::sqrt(retVal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

double& Vector::operator[](int i) const {
    if (i >= length || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Vector or Matrix"));
    
    return v[i];
}
Vector Vector::operator/(const double& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = v[i] / other;

    return vector;
}
Vector Vector::operator*(const double& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = v[i] * other;

    return vector;
}
Vector Vector::operator*(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = v[i] * other[i];

    return vector;
}
Vector Vector::operator+(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = v[i] + other[i];

    return vector;
}
Vector Vector::operator-(const Vector& other) const {
    Vector vector(length);
    
    for (int i = 0; i < length; i++)
        vector[i] = v[i] - other[i];

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
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aka vector product
Vector Vector::crossProduct(Vector lhs, Vector rhs) {
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
double Vector::dotProduct(Vector lhs, Vector rhs) {
    double retVal = 0;
    
    for (int i = 0; i < lhs.length; i++)
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

#pragma once

#include <string>
struct Vector {
private:
    double *v;
public:
    Vector(double a[]);
    Vector(double a, double b);
    Vector(double a, double b, double c);
    Vector(double a, double b, double c, double d);

    ~Vector();

    double x();
    double y();
    double z();
    double w();

    int length();
    double magnitude();

    double& operator[](int i) const;
    Vector operator/(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator*(const double& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    static Vector crossProduct(Vector lhs, Vector rhs);
    static Vector dotProduct(Vector lhs, Vector rhs);

    // static Vector unitNormal(Vector v1, Vector v2);
    // static Vector cosAngle(Vector v1, Vector v2);

    std::string toString();
};
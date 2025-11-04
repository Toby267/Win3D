#pragma once

#include <ostream>

struct Vector {
private:
    double *v;
    int _length;
public:
    //constructors/destructor
    Vector(int length);
    Vector(int length, double a[]);
    Vector(double a, double b);
    Vector(double a, double b, double c);
    Vector(double a, double b, double c, double d);
    ~Vector();

    //getters/setters
    double x();
    double y();
    double z();
    double w();
    int length();
    double magnitude();

    //operator overloads
    double& operator[](int i) const;
    Vector operator/(const double& other) const;
    Vector operator*(const double& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    //public methods
    static Vector crossProduct(Vector lhs, Vector rhs);
    static double dotProduct(Vector lhs, Vector rhs);

    static Vector unitNormal(Vector lhs, Vector rhs, Vector origin);
    static double cosAngle(Vector lhs, Vector rhs, Vector origin);

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};
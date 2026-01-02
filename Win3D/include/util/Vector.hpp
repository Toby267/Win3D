#pragma once

#include <ostream>

class Vector {
private:
    double vect[4]{};
    int length{4};
public:
    //constructors/destructor/rule of 5
    Vector() = default;
    Vector(int length);
    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double w);

    //getters/setters
    double& x();
    double& y();
    double& z();
    double& w();

    const double& x() const;
    const double& y() const;
    const double& z() const;
    const double& w() const;

    int getLength() const;
    double magnitude() const;

    //public methods
    Vector normalise();
    void cut();

    //operator overloads
    double& operator[](int i);
    const double& operator[](int i) const;

    Vector operator*(double other) const;
    Vector operator/(double other) const;
    Vector operator+(double other) const;
    Vector operator-(double other) const;

    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector operator+() const;
    Vector operator-() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

    //static methods
    static Vector crossProduct(const Vector& lhs, const Vector& rhs);
    static double dotProduct(const Vector& lhs, const Vector& rhs);

    static Vector unitNormal(const Vector& lhs, const Vector& rhs);
    static double cosAngle(const Vector& lhs, const Vector& rhs);
};

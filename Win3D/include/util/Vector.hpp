#pragma once

#include <ostream>

class Vector {
private:
    double *v;
    int length;
public:
    //constructors/destructor/rule of 5
    Vector();
    Vector(int _length);
    Vector(int _length, double a[]);
    Vector(double a, double b);
    Vector(double a, double b, double c);
    Vector(double a, double b, double c, double d);

    Vector(const Vector& other);                  //copy constructor
    Vector& operator=(const Vector& other);       //copy assignment operator
    Vector(Vector&& other) noexcept;              //move constructor
    Vector& operator=(Vector&& other) noexcept;   //move assignment operator
    ~Vector();                                    //destructor

    //getters/setters
    double& x();
    double& y();
    double& z();
    double& w();
    int getLength() const;
    double magnitude() const;

    //operator overloads
    double& operator[](int i) const;
    Vector operator/(const double& other) const;
    Vector operator*(const double& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

    //static methods
    static Vector crossProduct(Vector lhs, Vector rhs);
    static double dotProduct(Vector lhs, Vector rhs);

    static Vector unitNormal(Vector lhs, Vector rhs, Vector origin);
    static double cosAngle(Vector lhs, Vector rhs, Vector origin);
};

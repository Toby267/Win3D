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

    const double& x() const;
    const double& y() const;
    const double& z() const;
    const double& w() const;

    int getLength() const;
    double magnitude() const;

    //operator overloads
    double& operator[](int i);
    const double& operator[](int i) const;
    Vector operator/(double other) const;
    Vector operator*(double other) const;
    Vector operator*(const Vector& other) const;
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

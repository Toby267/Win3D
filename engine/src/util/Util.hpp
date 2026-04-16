#pragma once

#include <ostream>

/**
 * Class representing a vector of variable length between 1 and 4, and related methods
 */
class Vector {
private:
    double data[4]{};
    int length{4};
public:
    // constructors/destructor
    Vector() = default;
    Vector(int length);
    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double w);

    // getters/setters
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

    // public methods
    Vector normalise();
    static Vector asVec3(Vector& v);

    // operator overloads
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

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

    // static methods
    static Vector min();
    static Vector max();

    static Vector crossProduct(const Vector& lhs, const Vector& rhs);
    static double dotProduct(const Vector& lhs, const Vector& rhs);

    static Vector unitNormal(const Vector& lhs, const Vector& rhs);
    static double cosAngle(const Vector& lhs, const Vector& rhs);
};

/**
 * Class representing a matrix of variable length between 1x1 and 4x4, and related methods
 */
class Matrix {
private:
    Vector data[4]{};
    int rows = 4;
    int columns = 4;

public:
    // constructors/destructor
    Matrix() = default;
    Matrix(int rows, int columns);
    Matrix(int rows, const Vector (&a)[]);

    // getters/setters
    int getColumns() const;
    int getRows() const;

    static Matrix asMat3(Matrix& m);

    // operator overloads
    Vector& operator[](int i);
    const Vector& operator[](int i) const;

    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    // static methods
    static Matrix translate(double x, double y, double z);
    static Matrix scale(double x, double y, double z);
    static Matrix identity(int size);

    static Matrix rotation(double roll, double pitch, double yaw);
    static Matrix roll(double radians);
    static Matrix pitch(double radians);
    static Matrix yaw(double radians);

    static Matrix orthographic(double near, double far, double top, double right);
    static Matrix perspective(double n, double f, double aspect, double fov);

    static Matrix changeOfBasis(const Vector& position, const Vector& direction, const Vector& up);
};

/**
 * Class representing an rgba colour, and related methods
 */
class Colour {
private:
    Vector data;
public:
    // constructors/destructor
    Colour();
    Colour(double red, double green, double blue, double alpha);
    Colour(double red, double green, double blue);

    // getters/setters
    double& r();
    double& g();
    double& b();
    double& a();

    const double& r() const;
    const double& g() const;
    const double& b() const;
    const double& a() const;

    // public methods
    static Colour normalise(Colour c);
    static Colour denormalise(Colour c);

    // operator overloads
    Colour operator+(const Colour& other) const;
    Colour operator-(const Colour& other) const;
    Colour operator*(const Colour& other) const;
    Colour operator/(const Colour& other) const;
    
    Colour operator+(double other) const;
    Colour operator-(double other) const;
    Colour operator*(double other) const;
    Colour operator/(double other) const;

    Colour operator-() const;

    friend std::ostream& operator<<(std::ostream& os, const Colour& colour);

    // static methods
    static Colour white(), red(), green(), blue(), cyan(), magenta(), yellow();
};

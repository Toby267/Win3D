#pragma once

#include "Vector.hpp"

class Matrix {
private:
    Vector mat[4]{};
    int rows = 4, columns = 4;

public:
    //constructors/destructor/rule of 5
    Matrix() = default;
    Matrix(int rows, int columns);
    Matrix(int rows, const Vector (&a)[]);

    //getters/setters
    int getColumns() const;
    int getRows() const;

    //operator overloads
    Vector& operator[](int i);
    const Vector& operator[](int i) const;

    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    //static methods
    static Matrix translate(double x, double y, double z);
    static Matrix scale(double x, double y, double z);
    static Matrix identity(int size);

    static Matrix rotation(double roll, double pitch, double yaw);
    static Matrix roll(double rad);
    static Matrix pitch(double rad);
    static Matrix yaw(double rad);

    static Matrix orthographic(double near, double far, double top, double right);
    static Matrix perspective(double near, double far, double top, double right, double fov);

    static Matrix changeOfBasis(const Vector& position, const Vector& direction, const Vector& up);
};

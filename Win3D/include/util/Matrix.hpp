#pragma once

#include "Vector.hpp"

struct Matrix {
private:
    Vector **v;
public:
    Matrix(int rows, int columns, double **a);
    ~Matrix();

    int columns();
    int rows();

    // double& operator[][](int i, int j) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const Vector& other) const;

    static Matrix translate(double x, double y, double z);
    static Matrix scale(double x, double y, double z);
    static Matrix identity(double x, double y, double z);
    static Matrix project(double x, double y, double z);
    static Matrix roll(double x, double y, double z);
    static Matrix pitch(double x, double y, double z);
    static Matrix yaw(double x, double y, double z);

    std::string toString();
};
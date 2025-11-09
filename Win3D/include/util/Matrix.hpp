#pragma once

#include "Vector.hpp"

class Matrix {
private:
    Vector *m;
    int rows, columns;

public:
    //constructors/destructor/rule of 5
    Matrix(int _rows, int _columns);
    Matrix(int _rows, int _columns, double a[]);
    Matrix(int rows, Vector a[]);

    Matrix(const Matrix& other);                    //copy constructor
    Matrix& operator=(const Matrix& other);         //copy assignment operator
    Matrix(Matrix&& other) noexcept;                //move constructor
    Matrix& operator=(Matrix&& other) noexcept;     //move assignment operator
    ~Matrix();                                      //destructor

    //getters/setters
    int getColumns();
    int getRows();

    //operator overloads
    Vector& operator[](int i) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    //static methods
    static Matrix translate(double x, double y, double z);
    static Matrix scale(double x, double y, double z);
    static Matrix identity(int size);
    static Matrix project(double d);
    static Matrix rotation(double roll, double pitch, double yaw);
    static Matrix roll(double rad);
    static Matrix pitch(double rad);
    static Matrix yaw(double rad);
    static Matrix orthographic(Vector minimumCorner, Vector maximumCorner);
};

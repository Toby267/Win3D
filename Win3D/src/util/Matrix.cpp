#include "util/Util.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "util/Util.hpp"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------- [ CONSTRUCTORS/DESCTUCTOR/RULE OF 5 ] ------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(int r, int c) : rows(r), columns(c) {}

//const reference so that im not copying each vector in the array
Matrix::Matrix(int r, const Vector (&a)[]) : rows(r), columns(a[0].getLength()) {
    for (int i = 0; i < r; i++)
        data[i] = a[i];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Matrix::getColumns() const {
    return columns;
}
int Matrix::getRows() const {
    return rows;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector& Matrix::operator[](int i) {
    if (i >= rows || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Matrix"));
    
    return data[i];
}
const Vector& Matrix::operator[](int i) const {
    if (i >= rows || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Matrix"));
    
    return data[i];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (columns != other.rows) throw std::logic_error("Can't multiply matirx by matrix: columns and rows  do not match");
    
    Matrix matrix(rows, other.columns);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            for (int k = 0; k < other.rows; k++)  {
                matrix[i][j] += data[i][k] * other[k][j];
            }
        }
    }

    return matrix;
}
Vector Matrix::operator*(const Vector& other) const {
    if (columns != other.getLength()) throw std::logic_error("Can't multiply matirx by vector: columns and rows  do not match");

    Vector vector(other.getLength());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            vector[i] += data[i][j] * other[j];
        }
    }

    return vector;
}
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "\n";

    for (int i = 0; i < matrix.rows; i++)
        os << "|" << matrix[i] << "|\n";

    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::translate(double x, double y, double z) {
    return Matrix(4, (Vector[]){
        Vector{1, 0, 0, x},
        Vector{0, 1, 0, y},
        Vector{0, 0, 1, z},
        Vector{0, 0, 0, 1}
    });
}
Matrix Matrix::scale(double x, double y, double z) {
    return Matrix(4, (Vector[]){
        Vector{x, 0, 0, 0},
        Vector{0, y, 0, 0},
        Vector{0, 0, z, 0},
        Vector{0, 0, 0, 1}
    });
}
Matrix Matrix::identity(int size) {
    double s = (double)size;
    return Matrix(4, (Vector[]){
        Vector{s, 0, 0, 0},
        Vector{0, s, 0, 0},
        Vector{0, 0, s, 0},
        Vector{0, 0, 0, s}
    });
}
Matrix Matrix::rotation(double roll, double pitch, double yaw) {
    return Matrix::roll(roll) * Matrix::pitch(pitch) * Matrix::yaw(yaw);
}
Matrix Matrix::roll(double rad) {
    double ca = std::cos(rad);
    double sa = std::sin(rad);
    double nsa = -1.0 * sa;
    return Matrix(4, (Vector[]){
        Vector{ca, nsa, 0, 0},
        Vector{sa,  ca, 0, 0},
        Vector{0,    0, 1, 0},
        Vector{0,    0, 0, 1}
    });
}
Matrix Matrix::pitch(double radians) {
    double ca = std::cos(radians);
    double sa = std::sin(radians);
    double nsa = -1.0 * sa;
    return Matrix(4, (Vector[]){
        Vector{1,  0,   0, 0},
        Vector{0, ca, nsa, 0},
        Vector{0, sa,  ca, 0},
        Vector{0,  0,   0, 1}
    });
}
Matrix Matrix::yaw(double radians) {
    double ca = std::cos(radians);
    double sa = std::sin(radians);
    double nsa = -1.0 * sa;
    return Matrix(4, (Vector[]){
        Vector{ca,  0, sa, 0},
        Vector{0,   1, 0,  0},
        Vector{nsa, 0, ca, 0},
        Vector{0,   0, 0,  1}
    });
}

/**
 * retuns the perspective transform matrix that maps to the canonical view volume defined in the geometry processor.
 * assumes l = -r, b = -t
 */
Matrix Matrix::orthographic(double n, double f, double t, double r) {
    double zs = 2.0/(f-n);
    double zt = -(f+n)/(f-n);

    return Matrix(4, (Vector[]){
        Vector(1/r, 0, 0, 0),
        Vector(0, 1/t, 0, 0),
        Vector(0, 0, zs, zt),
        Vector(0, 0, 0, 1)
    });
}

/**
 * retuns the perspective transform matrix that maps to the canonical view volume defined in the geometry processor.
 * fov assumed to be in radians
 * assumes l = -r and b = -t      those assumptions allowed me to simplify to this:
 */
Matrix Matrix::perspective(double n, double f, double aspect, double fov) {
    // double aspect = r/t;

    double _00 = 1 / ( aspect * std::tan(fov / 2) );
    double _11 = 1 / ( std::tan(fov / 2) );

    double _22 = (f+n) / (f-n);
    double _23 = -2.0 * (f*n) / (f-n);
    
    return Matrix(4, (Vector[]){
        Vector{_00,   0,   0,    0},
        Vector{  0, _11,   0,    0},
        Vector{  0,   0, _22,  _23},
        Vector{  0,   0,   1,    0}
    });
}

//returns a matrix that transforms objects to a view assuming the cameria is at position position, looking down direction, and its up is up
Matrix Matrix::changeOfBasis(const Vector& position, const Vector& direction, const Vector& up) {    
    Vector rightBasis = -Vector::unitNormal(direction, up);
    Vector upBasis    = Vector::crossProduct(direction, rightBasis);

    return Matrix(4, (Vector[]){
        rightBasis,
        upBasis,
        direction,
        Vector(0, 0, 0, 1)
    });
}
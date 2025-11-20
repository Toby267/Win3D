#include "util/Matrix.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "util/Vector.hpp"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------- [ CONSTRUCTORS/DESCTUCTOR/RULE OF 5 ] ------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns) {}

//const reference so that im not copying each vector in the array
Matrix::Matrix(int rows, const Vector (&a)[]) : rows(rows), columns(a[0].getLength()) {
    for (int i = 0; i < rows; i++)
        mat[i] = a[i];
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
    
    return mat[i];
}
const Vector& Matrix::operator[](int i) const {
    if (i >= rows || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Matrix"));
    
    return mat[i];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (columns != other.rows) throw std::logic_error("Can't multiply matirx by matrix: columns and rows  do not match");
    
    Matrix matrix(rows, other.columns);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            for (int k = 0; k < other.rows; k++)  {
                matrix[i][j] += mat[i][k] * other[k][j];
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
            vector[i] += mat[i][j] * other[j];
        }
    }

    return vector;
}
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << "\n";

    for (int i = 0; i < m.rows; i++)
        os << "|" << m[i] << "|\n";

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
Matrix Matrix::pitch(double rad) {
    double ca = std::cos(rad);
    double sa = std::sin(rad);
    double nsa = -1.0 * sa;
    return Matrix(4, (Vector[]){
        Vector{1,  0,   0, 0},
        Vector{0, ca, nsa, 0},
        Vector{0, sa,  ca, 0},
        Vector{0,  0,   0, 1}
    });
}
Matrix Matrix::yaw(double rad) {
    double ca = std::cos(rad);
    double sa = std::sin(rad);
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
 * assumes l = -r, b = -t, and t = -f
 */
Matrix Matrix::orthographic(double l, double b, double n, double r, double t, double f) {
    double xs = 2.0/(r-l);
    double ys = 2.0/(t-b);
    double zs = 2.0/(f-n);

    double xt = (r+l)/2.0;
    double yt = (t+b)/2.0;
    double zt = (f+n)/2.0;

    return Matrix::scale(xs, ys, zs) * Matrix::translate(-xt, -yt, -zt);
}

/**
 * retuns the perspective transform matrix that maps to the canonical view volume defined in the geometry processor.
 * assumes l = -r, b = -t, and t = -f       those assumptions allowed me to simplify to this:
 */
Matrix Matrix::perspective(double l, double b, double n, double r, double t, double f) {
    Matrix perspective(4, (Vector[]){
        Vector{f,   0,   0,    0},
        Vector{ 0, f,   0,    0},
        Vector{  0,   0, 2*f, f*n},
        Vector{  0,   0,   1,   0}
    });

    return Matrix::orthographic(l, b, n, r, t, f) * perspective;
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
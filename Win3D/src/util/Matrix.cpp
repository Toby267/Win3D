#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------- [ CONSTRUCTORS/DESCTUCTOR/RULE OF 5 ] ------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(int _rows, int _columns) {
    rows = _rows;
    columns = _columns;

    m = new Vector[rows];
    for (int i = 0; i < rows; i++)
        m[i] = Vector(columns);
}
Matrix::Matrix(int _rows, int _columns, double a[]) {
    rows = _rows;
    columns = _columns;

    m = new Vector[rows];
    for (int i = 0; i < rows; i++)
        m[i] = Vector(columns);

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++, k++) {
            m[i][j] = a[k];
        }
    }
}
Matrix::Matrix(int _rows, Vector a[]) {
    rows = _rows;
    columns = a[0].getLength();

    m = new Vector[rows];
    for (int i = 0; i < rows; i++)
        m[i] = a[i];
}

//copy constructor
Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    columns = other.columns;

    m = new Vector[rows];
    for (int i = 0; i < rows; i++)
        m[i] = other.m[i];
}
//copy assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        if (m) delete[] m;

        rows = other.rows;
        columns = other.columns;

        m = new Vector[rows];
        for (int i = 0; i < rows; i++)
            m[i] = other.m[i];
    }

    return *this;
}
//move constructor
Matrix::Matrix(Matrix&& other) noexcept {
    rows = other.rows;
    columns = other.columns;
    m = other.m;

    other.rows = 0;
    other.columns = 0;
    other.m = nullptr;
}
//move assignment operator
Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        if (m) delete[] m;

        rows = other.rows;
        columns = other.columns;
        m = other.m;

        other.rows = 0;
        other.columns = 0;
        other.m = nullptr;
    }

    return *this;
}
//destructor
Matrix::~Matrix() {
    if (m) delete[] m;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Matrix::getColumns() {
    return columns;
}
int Matrix::getRows() {
    return rows;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector& Matrix::operator[](int i) const {
    if (i >= rows || i < 0)
        throw std::out_of_range(std::string("Index: " + std::to_string(i) + " out of range of Matrix"));
    
    return m[i];
}
Matrix Matrix::operator*(const Matrix& other) const {
    if (columns != other.rows) throw std::logic_error("Can't multiply matirx by matrix: columns and rows  do not match");
    
    Matrix matrix(rows, other.columns);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            for (int k = 0; k < other.rows; k++)  {
                matrix[i][j] += m[i][k] * other[k][j];
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
            vector[i] += m[i][j] * other[j];
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
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
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
Matrix Matrix::project(double d) {
    return Matrix(4, (Vector[]){
        Vector{1, 0,      0, 0},
        Vector{0, 1,      0, 0},
        Vector{0, 0,      1, 0},
        Vector{0, 0, -(1/d), 0}
    });
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
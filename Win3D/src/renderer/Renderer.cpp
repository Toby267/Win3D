#include "renderer/Renderer.hpp"
#include "util/Vector.hpp"
#include "util/Matrix.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) : window(width, height), bitmap(width, height) {
    while (window.isAlive()) {
        int num = rand() % 3;

        // int x = 0, y = 0;
        // double ySlope = (double)height / (double)width;
        // while (x != 2*width) {
            // y = ySlope * x;
            // bitmap.DrawLine(Vector(x, 0, 0), Vector(0, y, 0), Colour(255, 0, 0, 255), Colour(0, 255, 0, 255));
            // x ++;
        // }
        
        for (int j = 0; j < height; j++)
            bitmap.DrawLine(Vector(0, j, 0), Vector(width-1, j, 0), Colour(255, 0, 0, 255), Colour(0, 255, 0, 255));

        // for (int i = 0; i < width; i++)
            // bitmap.DrawLine(Vector(i, 0, 0), Vector(i, height-1, 0), Colour(255, 0, 0, 255), Colour(0, 255, 0, 255));

        window.update(bitmap.getFrameBuffer());
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Renderer::test() {
    // std::cout << "allocation count: " << allocationCount << '\n';
    Vector camera = Vector::unitNormal(
        Vector(1, 0, 0, 1),
        Vector(0, 0, 0, 1),
        Vector(0, 1, 0, 1)
    );

    std::cout << "camera: " << camera << '\n';
    Vector a = Vector(1, 2, 3);
    Vector b = Vector(4, 5, 6);
    Vector c = Vector(5, 7, 9);
    Vector d = Vector(3, 4, 5);
    Vector e = Vector(6, 8, 10);
    Vector f = Vector(2, -3, 4);

    Vector g = Vector(5, 6, 10);
    Vector h = Vector(1, 2, 3);


    std::cout << "Setting v[1]=5 in " << h;
    h[1] = 5;
    std::cout << "gives " << h << '\n';

    std::cout << "Length of " << a << " is " << a.getLength() << '\n';
    std::cout << "Given v = " << a << ", v[0] is " << a[0] << ", v[1] is " << a[1] << ", and v[2] is " << a[2] << '\n';

    std::cout << a << " + " << b << " = " << a+b << '\n';
    std::cout << c << " - " << b << " = " << c-b << '\n';
    std::cout << b << " - " << c << " = " << b-c << '\n';

    std::cout << "Given v = " << d << ", 2v = " << d*2 << '\n';
    std::cout << "Given v = " << e << ", v/2 = " << e/2 << '\n';
    std::cout << f << " * " << g << " = " << f*g << '\n';
    Vector i = Vector::crossProduct(f, g);
    std::cout << f << " X " << g << " = " << i << '\n';
    std::cout << f << " . " << g << " = ";
    std::cout <<  Vector::dotProduct(f, g) << '\n';
    std::cout << "magnitude of " << a << ": " << a.magnitude() << '\n';

    //exceptions:
    // std::cout << a[3];
    // std::cout << a[-1];
    // a[-1] = 3;

    Matrix r = Matrix(3, (Vector[]){
        Vector{1, 2},
        Vector{3, 4},
        Vector{5, 6}
    });

    Matrix s = Matrix(2, 3, (double[]){
        1, 2, 3,
        4, 5, 6,
    });

    Matrix m = Matrix(2, 2, (double[]){
        1, 2,
        3, 4
    });

    Matrix v = Matrix(2, 1, (double[]){
        10,
        20
    });

    Matrix n = Matrix(2, 2, (double[]){
        5, 6,
        7, 8
    });

    std::cout << "Columns and Rows of the following matrix are " << r.getColumns() << ", " << r.getRows() << "\n" << r;
    std::cout << "Given the matrix: " << m;
    std::cout << "...multiplying by the column vector " << v << "T gives\n" << m*v;
    std::cout << "Given the following two vectors:\n" << r << '\n' << s;
    std::cout << "multiplying them gives: \n" << r*s;
    // std::cout << "allocation count: " << allocationCount << '\n';
}

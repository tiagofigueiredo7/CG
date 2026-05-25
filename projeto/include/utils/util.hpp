#ifndef UTIL_HPP
#define UTIL_HPP

// Bibliotecas uteis
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// Bibliotecas locais
#include "generator/PrimitiveBuffers.hpp"

using namespace std;

namespace util {

    typedef struct point3D {
        float x;
        float y;
        float z;
    } Point3D;

    typedef struct plane {
        float a;
        float b;
        float c;
        float d;
    } Plane;

    bool checkInputEngine(const int parameters , const string scene);
    
    bool checkInputGenerator(const int parameters , const string figure);

    void multMatrixVector(float *m, float *v, float *res);

    void multiMatrixVector_ColumnMajor(float *m, float *v, float *res);

    void buildRotMatrix(float *x, float *y, float *z, float *m);

    void cross(float *a, float *b, float *res);

    void normalize(float *a);
}

#endif

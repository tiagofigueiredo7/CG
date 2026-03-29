#ifndef UTIL_HPP
#define UTIL_HPP

// Bibliotecas uteis
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

namespace util {

    void storeVertices(const vector<float>& vertices, const string& file);
    
    bool checkInput(const int parameters , const string figure);

    void addTriangle(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

    void multMatrixVector(float *m, float *v, float *res);

    void buildRotMatrix(float *x, float *y, float *z, float *m);

    void cross(float *a, float *b, float *res);

    void normalize(float *a);
}

#endif

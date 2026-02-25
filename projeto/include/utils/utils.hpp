#ifndef UTILS_HPP
#define UTILS_HPP

// Bibliotecas uteis
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace utils {
    bool checkInput(const int parameters , const string figure);

    void addTriangle(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
}

#endif

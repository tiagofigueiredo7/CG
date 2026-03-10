#ifndef BEZIER_HPP
#define BEZIER_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/Patch.hpp"

using namespace std;
using namespace util;

vector<float> generateBezierModel(Patch* data, int tesselation);

#endif
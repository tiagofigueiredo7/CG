#ifndef MOBIUS_HPP
#define MOBIUS_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

vector <float> generateMobiusStrip(float radius, float width, int slices);

#endif

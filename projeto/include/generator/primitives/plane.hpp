#ifndef PLANE_HPP
#define PLANE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

PrimitiveBuffers generatePlane(float length, int divisions);

#endif

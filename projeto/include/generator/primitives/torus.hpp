#ifndef TORUS_HPP
#define TORUS_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

PrimitiveBuffers generateTorus(float majorRadius, float minorRadius, int slices, int stacks);

#endif
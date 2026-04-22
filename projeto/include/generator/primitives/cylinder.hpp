#ifndef CYLINDER_HPP
#define CYLINDER_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

PrimitiveBuffers generateCylinder(float radius, float height, int slices);

#endif
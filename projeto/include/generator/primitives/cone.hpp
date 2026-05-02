#ifndef CONE_HPP
#define CONE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

PrimitiveBuffers generateCone(float radius, float height, int slices, int stacks);

#endif

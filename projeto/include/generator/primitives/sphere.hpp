#ifndef SPHERE_HPP
#define SPHERE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

PrimitiveBuffers generateSphere(float radius, int slices, int stacks);

#endif
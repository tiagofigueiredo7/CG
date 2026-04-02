#ifndef NOISESPHERE_HPP
#define NOISESPHERE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

/**
 * radius: raio da esfera
 * slices: Divisões em longitude (u)
 * stacks: Divisões em latitude (v)
 * amplitude: Intensidade da deformação
 */

float noise(float u, float v, float amplitude);

vector <float> generateNoiseSphere(float radius, int slices, int stacks, float amplitude);

#endif

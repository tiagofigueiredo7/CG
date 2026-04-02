#ifndef NOISESPHERE_HPP
#define NOISESPHERE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

vector <float> generateNoiseSphere(float radius, int slices, int stacks);

#endif

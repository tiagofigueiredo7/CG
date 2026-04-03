#ifndef KLEINBOTTLE_HPP
#define KLEINBOTTLE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

/***
 * radius: Raio do anel central
 * slices: Divisões em longitude (u)
 * stacks: Divisões em latitude (v)
 */

vector <float> generateKleinBottle(float radius, int slices, int stacks);

#endif
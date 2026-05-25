#ifndef KLEINBOTTLE_HPP
#define KLEINBOTTLE_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/PrimitiveBuffers.hpp"

using namespace std;
using namespace util;

/***
 * slices: Divisões em longitude (u)
 * stacks: Divisões em latitude (v)
 */

PrimitiveBuffers generateKleinBottle(int slices, int stacks);

#endif
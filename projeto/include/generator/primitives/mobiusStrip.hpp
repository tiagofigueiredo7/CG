#ifndef MOBIUSSTRIP_HPP
#define MOBIUSSTRIP_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

/***
 * radius: Raio do anel central
 * width: Meia-largura da fita
 * slices: Divisões ao longo de u (resolução)
 */

vector <float> generateMobiusStrip(float radius, float width, int slices);

#endif

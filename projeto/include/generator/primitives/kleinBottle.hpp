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
 * scale: Fator de escala para o tamanho geral da garrafa
 * tubeRadius: Raio do tubo da garrafa (ajusta a "espessura" da garrafa)
 * heightStretch: Fator de alongamento vertical (ajusta a "altura" da garrafa)
 */

PrimitiveBuffers generateKleinBottle(int slices, int stacks, float scale, float tubeRadius, float heightStretch);

#endif
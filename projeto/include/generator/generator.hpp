#ifndef GENERATOR_HPP
#define GENERATOR_HPP

// Bibliotecas uteis
#include <string>
#include <iostream>
#include <fstream>

// Bibliotecas locais
#include "utils/util.hpp"
#include "primitives/plane.hpp"
#include "primitives/box.hpp"
#include "primitives/sphere.hpp"
#include "primitives/cone.hpp"
#include "primitives/torus.hpp"
#include "primitives/cylinder.hpp"
#include "primitives/bezier.hpp"
#include "generator/Patch.hpp"

using namespace std;

void storeVertices(const vector<float>& vertices, const string& file);

int main(int argc, char** argv);

#endif

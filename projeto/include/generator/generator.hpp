#ifndef GENERATOR_HPP
#define GENERATOR_HPP

// Bibliotecas uteis
#include <string>
#include <iostream>
#include <fstream>

// Bibliotecas locais
#include "plane.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "cone.hpp"
#include "torus.hpp"

using namespace std;

void storeVertices(const vector<float>& vertices, const string& file);

int main(int argc, char** argv);

#endif

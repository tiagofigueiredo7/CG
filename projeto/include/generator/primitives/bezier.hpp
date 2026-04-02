#ifndef BEZIER_HPP
#define BEZIER_HPP

// Bibliotecas uteis
#include <cmath>

// Bibliotecas locais
#include "utils/util.hpp"
#include "generator/Patch.hpp"
#include "Point3D.hpp"

using namespace std;
using namespace util;

Point3D bezier(float u, float v, vector<float>* control_points);

vector<float> getValores_in_Indices(vector<float>* indices, vector<float>* control_points);

vector<float> generateBezierModel(char* file_path, int tesselation);

#endif
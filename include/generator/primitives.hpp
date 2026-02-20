#pragma once

#include <cmath>

#include "utils/utils.hpp"
using namespace std;

vector <float> generatePlane(float length, int divisions);
vector <float> generateBox(float length, int divisions);
vector <float> generateSphere(float radius, int slices, int stacks);
vector <float> generateCone(float radius, float height, int slices, int stacks);
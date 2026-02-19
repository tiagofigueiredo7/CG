#pragma once

#include <cmath>

#include "utils/utils.hpp"

std::vector <float> generatePlane(float length, int divisions);
std::vector <float> generateBox(float length, int divisions);
std::vector <float> generateSphere(float radius, int slices, int stacks);
std::vector <float> generateCone(float radius, float height, int slices, int stacks);
#include "generator/Patch.hpp"

Patch::Patch() {
    this->patches_count = 0;
    this->control_points_count = 0;
    this->indices_first_patch = vector<float>();
    this->indices_second_patch = vector<float>();
    this->control_points_values = vector<float>();
}

int Patch::getPatchesCount() {
    return this->patches_count;
}

vector<float> Patch::getIndicesFirstPatch() {
    return this->indices_first_patch;
}

vector<float> Patch::getIndicesSecondPatch() {
    return this->indices_second_patch;
}

int Patch::getControlPointsCount() {
    return this->control_points_count;
}

vector<float> Patch::getControlPointsValues() {
    return this->control_points_values;
}

void Patch::parse_Patch_File(char* file) {}
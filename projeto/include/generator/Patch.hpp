#ifndef PATCH_HPP
#define PATCH_HPP

// Bibliotecas uteis
#include <vector>

// Bibliotecas locais
#include "utils/util.hpp"

using namespace std;

class Patch {
    private:
        int patches_count;
        vector<float> indices_first_patch;
        vector<float> indices_second_patch;

        int control_points_count;
        vector<float> control_points_values; // Este vetor guarda os 3 valores de cada control point

    public:
        Patch();
        void parse_Patch_File(char* file);

        int getPatchesCount();
        vector<float> getIndicesFirstPatch();
        vector<float> getIndicesSecondPatch();

        int getControlPointsCount();
        vector<float> getControlPointsValues();
};


#endif
#ifndef PATCH_HPP
#define PATCH_HPP

// Bibliotecas uteis
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

// Bibliotecas locais
#include "utils/util.hpp"

using namespace std;

class BezierPatch {
    private:
        int patches_count;
        vector<float>** indices_patch;

        int control_points_count;
        vector<float> control_points_values; // Este vetor guarda os 3 valores de cada control point

    public:

        BezierPatch();
        ~BezierPatch();

        void parse_Patch_File(char* file_path);

        int getPatchesCount();
        vector<float>* getIndicesPatch(int index); 

        int getControlPointsCount();
        vector<float> getControlPointsValues();

        void setPatchesCount(int count);
        void setControlPointsCount(int count);
};


#endif
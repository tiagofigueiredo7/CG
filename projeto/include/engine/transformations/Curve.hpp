#ifndef CURVE_HPP
#define CURVE_HPP

#include "engine/transformations/Transformation.hpp"

#include <vector>
#include <stdlib.h>
using namespace std;

class Curve : public Transformation {

    private:
        bool alygn;
        float time;
        vector<float*> points;

    public:
        Curve(bool alygn, float time);
        Curve();
        ~Curve();

        bool getAlygn();
        float getTime();
        vector<float*> getPoints();

        void setAlygn(bool novoAlygn);
        void setTime(float novoTime);
        void addPoint(float* arr);
    

};


#endif
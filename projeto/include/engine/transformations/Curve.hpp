#ifndef CURVE_HPP
#define CURVE_HPP

#include "engine/transformations/Transformation.hpp"

#include <vector>
#include <stdlib.h>
using namespace std;

class Curve : public Transformation {

    private:
        bool align;
        float time;
        vector<float*> points;

    public:
        Curve(bool align, float time);
        Curve();
        ~Curve();

        bool getAlign();
        float getTime();
        vector<float*> getPoints();

        void setAlign(bool novoAlign);
        void setTime(float novoTime);
        void addPoint(float* arr);
    

};


#endif
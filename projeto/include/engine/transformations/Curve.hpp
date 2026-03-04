#ifndef CURVE_HPP
#define CURVE_HPP

#include "engine/transformations/Transformation.hpp"

#include <vector>
using namespace std;

class Curve : private Transformation {

    private:
        bool alygn;
        float time;
        vector<float*> points;

    public:
        Curve(bool alygn, float time, vector<float*>* points);
        Curve();

        bool getAlygn();
        float getTime();
        vector<float*> getPoints();

        void setAlygn(bool novoAlygn);
        void setTime(float novoTime);
        void setPoints(vector<float*>* novoPoints);
    

};


#endif
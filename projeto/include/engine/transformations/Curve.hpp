#ifndef CURVE_HPP
#define CURVE_HPP

#include "engine/transformations/Transformation.hpp"
#include "utils/util.hpp"

#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

#include <vector>
#include <stdlib.h>
using namespace std;
using namespace util;

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

        void renderCatmullRomCurve();
        void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
        void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
    

};


#endif
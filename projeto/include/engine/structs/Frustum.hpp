#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

#include "camera/Camera.hpp"
#include <stdlib.h>
#include "utils/util.hpp"
#include <math.h>

using namespace util;

typedef struct plane {
    float a;
    float b;
    float c;
    float d;
} Plane;

class Frustum {
    private:
        Plane planes[6];
        void createPlane(Plane& plane, float* p1, float* p2, float* p3);
        
    public:
        Frustum();

        bool pointInFrustum(float x, float y, float z);
        bool sphereInFrustum(float x, float y, float z, float radius);
        void updateFrustum(Camera* cam, float fov, float nearDist, float farDist, float ratio);
        void drawFrustum(Camera* cam, float fov, float nearDist, float farDist, float ratio);

};


#endif

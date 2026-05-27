#ifndef FPS_HPP
#define FPS_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

#include <string>

using namespace std;

class FPS {
    private:
        float timebase;
        int frame;
        float fps;
        string fpsString;
        
    public:
        FPS();

        void updateFPS();

        string getFPSString();

        

        

};

#endif

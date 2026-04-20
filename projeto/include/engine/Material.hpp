#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

class Material {
    private:
        float difuse[4];
        float ambient[4];
        float specular[4];
        float emissive[4];
        float shininess;
    public:
        Material();

        void aplicarMaterial();

        void setDifuse(float r, float g, float b, float a);
        void setAmbient(float r, float g, float b, float a);
        void setSpecular(float r, float g, float b, float a);
        void setEmissive(float r, float g, float b, float a);
        void setShininess(float s);

        

};


#endif

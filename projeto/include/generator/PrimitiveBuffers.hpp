#ifndef PRIMITIVEBUFFERS_HPP
#define PRIMITIVEBUFFERS_HPP

// Bibliotecas uteis
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class PrimitiveBuffers {
    private:
        vector<float> vertices;
        vector<float> normais;
        vector<float> textures;

        float raio_esfera;
    public:
        PrimitiveBuffers();

        vector<float> getVertices();
        vector<float> getNormais();
        vector<float> getTextures();

        void addTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
        void addNormals(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
        void addTextureCoordinates(float u1, float v1, float u2, float v2, float u3, float v3);

        void storeBuffers(string file); 

        void setRaioEsfera(float raio);
        float getRaioEsfera();
};


#endif
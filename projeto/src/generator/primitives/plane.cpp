#include "generator/primitives/plane.hpp"

// Cria os vértices de um plano
vector <float> generatePlane(float length, int divisions) {
    vector <float> vertices;
    float half = length / 2.0f; 
    float divlength = length / divisions; 
    
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = (j * divlength) - half;
            float x2 = x1 + divlength;
            float z1 = (i * divlength) - half; 
            float z2 = z1 + divlength;

            addTriangle(vertices, x1, 0, z1, x2, 0, z2, x2, 0, z1);
            addTriangle(vertices, x1, 0, z1, x1, 0, z2, x2, 0, z2);
        } 
    } 
    return vertices;
}

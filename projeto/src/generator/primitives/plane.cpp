#include "generator/primitives/plane.hpp"

// Cria os vértices de um plano
PrimitiveBuffers generatePlane(float length, int divisions) {
    PrimitiveBuffers buffers = PrimitiveBuffers();
    float half = length / 2.0f; 
    float divlength = length / divisions; 
    
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = (j * divlength) - half;
            float x2 = x1 + divlength;
            float z1 = (i * divlength) - half; 
            float z2 = z1 + divlength;

            buffers.addTriangle(x1, 0, z1, x2, 0, z2, x2, 0, z1);
            buffers.addTriangle(x1, 0, z1, x1, 0, z2, x2, 0, z2);
        } 
    } 
    return buffers;
}

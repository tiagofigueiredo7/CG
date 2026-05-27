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


            float u1 = (float)j / divisions;
            float u2 = (float)(j + 1) / divisions;
            float v1 = (float)i / divisions;
            float v2 = (float)(i + 1) / divisions;

            buffers.addTriangle(x1, 0, z1, x2, 0, z2, x2, 0, z1);
            buffers.addNormals(0, 1, 0, 0, 1, 0, 0, 1, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);


            buffers.addTriangle(x1, 0, z1, x1, 0, z2, x2, 0, z2);
            buffers.addNormals(0, 1, 0, 0, 1, 0, 0, 1, 0);
            buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);

        } 
    }
    
    // Calcular centro e raio a partir dos vértices gerados
    vector<float> verts = buffers.getVertices();
    int totalVertices = (int)verts.size() / 3;
    if (totalVertices > 0) {
        buffers.setCenter(0, 0, 0); // centro do plano é a origem
        buffers.setRaioEsfera(length * sqrt(2) / 2.0f); // raio da esfera circunscrita ao plano
    }

    return buffers;
}

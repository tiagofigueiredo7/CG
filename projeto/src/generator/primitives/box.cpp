#include "generator/primitives/box.hpp"

// Depois alterar generateBox para usar generatePlane? Código mais limpo

// Cria os vértices de uma caixa/cubo
PrimitiveBuffers generateBox(float length, int divisions) {
    PrimitiveBuffers buffers = PrimitiveBuffers();
    float half = length / 2.0f;
    float divlength = length / divisions;

    // faces do plano XZ
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        	float x1 = (j * divlength) - half;
            float x2 = x1 + divlength;
            float z1 = (i * divlength) - half;
            float z2 = z1 + divlength;
            float y1 = half;
            float y2 = -half;

            // plano "de cima"
            
            buffers.addTriangle(x1, y1, z1, x2, y1, z2, x2, y1, z1);
            buffers.addTriangle(x1, y1, z1, x1, y1, z2, x2, y1, z2);

            // plano "de baixo"
            buffers.addTriangle(x1, y2, z1, x2, y2, z1, x2, y2, z2);
            buffers.addTriangle(x1, y2, z1, x2, y2, z2, x1, y2, z2);
        }
    }

    // faces do plano XY
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = (j * divlength) - half;
            float x2 = x1 + divlength;
            float y1 = (i * divlength) - half;
            float y2 = y1 + divlength;
            float z1 = half;
            float z2 = -half;

            // plano "da frente"
            buffers.addTriangle(x1, y1, z1, x2, y2, z1, x1, y2, z1);
            buffers.addTriangle(x1, y1, z1, x2, y1, z1, x2, y2, z1);

            // plano "de trás"
			buffers.addTriangle(x1, y1, z2, x1, y2, z2, x2, y2, z2);
			buffers.addTriangle(x1, y1, z2, x2, y2, z2, x2, y1, z2);
        }
    }

    // faces do plano YZ
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = half;
            float x2 = -half;
            float y1 = (i * divlength) - half;
            float y2 = y1 + divlength;
            float z1 = (j * divlength) - half;
            float z2 = z1 + divlength;

            // plano "da direita"
            buffers.addTriangle(x1, y1, z1, x1, y2, z2, x1, y1, z2);
            buffers.addTriangle(x1, y1, z1, x1, y2, z1, x1, y2, z2);

            // plano "da esquerda"
            buffers.addTriangle(x2, y1, z1, x2, y1, z2, x2, y2, z2);
            buffers.addTriangle(x2, y1, z1, x2, y2, z2, x2, y2, z1);
        }
    }

    return buffers;
}

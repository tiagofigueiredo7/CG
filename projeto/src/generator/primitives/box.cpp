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

            float u1 = (float)j / divisions;
            float u2 = (float)(j + 1) / divisions;
            float v1 = (float)i / divisions;
            float v2 = (float)(i + 1) / divisions;

            // plano "de cima"
            buffers.addTriangle(x1, y1, z1, x2, y1, z2, x2, y1, z1);
            buffers.addNormals(0, 1, 0, 0, 1, 0, 0, 1, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);

            buffers.addTriangle(x1, y1, z1, x1, y1, z2, x2, y1, z2);
            buffers.addNormals(0, 1, 0, 0, 1, 0, 0, 1, 0);
            buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);

            // plano "de baixo"
            buffers.addTriangle(x1, y2, z1, x2, y2, z1, x2, y2, z2);
            buffers.addNormals(0, -1, 0, 0, -1, 0, 0, -1, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v1, u2, v2);

            buffers.addTriangle(x1, y2, z1, x2, y2, z2, x1, y2, z2);
            buffers.addNormals(0, -1, 0, 0, -1, 0, 0, -1, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u1, v2);
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

            float u1 = (float)j / divisions;
            float u2 = (float)(j + 1) / divisions;
            float v1 = (float)i / divisions;
            float v2 = (float)(i + 1) / divisions;

            // plano "da frente"
            buffers.addTriangle(x1, y1, z1, x2, y2, z1, x1, y2, z1);
            buffers.addNormals(0, 0, 1, 0, 0, 1, 0, 0, 1);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);

            buffers.addTriangle(x1, y1, z1, x2, y1, z1, x2, y2, z1);
            buffers.addNormals(0, 0, 1, 0, 0, 1, 0, 0, 1);
            buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);

            // plano "de trás"
			buffers.addTriangle(x1, y1, z2, x1, y2, z2, x2, y2, z2);
            buffers.addNormals(0, 0, -1, 0, 0, -1, 0, 0, -1);
            buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);


			buffers.addTriangle(x1, y1, z2, x2, y2, z2, x2, y1, z2);
            buffers.addNormals(0, 0, -1, 0, 0, -1, 0, 0, -1);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);
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

            float u1 = (float)j / divisions;
            float u2 = (float)(j + 1) / divisions;
            float v1 = (float)i / divisions;
            float v2 = (float)(i + 1) / divisions;

            // plano "da direita"
            buffers.addTriangle(x1, y1, z1, x1, y2, z2, x1, y1, z2);
            buffers.addNormals(1, 0, 0, 1, 0, 0, 1, 0, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u1, v2);

            buffers.addTriangle(x1, y1, z1, x1, y2, z1, x1, y2, z2);
            buffers.addNormals(1, 0, 0, 1, 0, 0, 1, 0, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v1, u2, v2);

            // plano "da esquerda"
            buffers.addTriangle(x2, y1, z1, x2, y1, z2, x2, y2, z2);
            buffers.addNormals(-1, 0, 0, -1, 0, 0, -1, 0, 0);
            buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);

            buffers.addTriangle(x2, y1, z1, x2, y2, z2, x2, y2, z1);
            buffers.addNormals(-1, 0, 0, -1, 0, 0, -1, 0, 0);
            buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);
        }
    }

    // Calcular centro e raio a partir dos vértices gerados
    vector<float> verts = buffers.getVertices();
    int totalVertices = (int)verts.size() / 3;
    if (totalVertices > 0) {
        buffers.setCenter(0,0,0); // centro da caixa é a origem
        buffers.setRaioEsfera(length * sqrt(3) / 2.0f); // raio da esfera circunscrita à caixa
    }

    return buffers;
}

#include "generator/primitives/cylinder.hpp"

PrimitiveBuffers generateCylinder(float radius, float height, int slices){
    PrimitiveBuffers buffers = PrimitiveBuffers();

    // Delta alpha
	float delta_alpha = 2*M_PI/slices;

    // Alturas
    float h_cima = height/2;       // Altura da base de cima
    float h_baixo = -height/2;     // Altura da base de baixo

	for(int i = 0; i < slices; i++){

		// Angulo alpha
		float alpha = i * delta_alpha;
		float nextAlpha = (i+1) * delta_alpha ;

		// Posições
		float x1 = sin(alpha) * radius;     // Posição x do ponto atual
		float x2 = sin(nextAlpha) * radius; // Posição x do próximo ponto

		float z1 = cos(alpha) * radius;     // Posição z do ponto atual
		float z2 = cos(nextAlpha) * radius; // Posição z do próximo ponto


        // Normais radiais para a superfície lateral
        float nx1 = sin(alpha);
        float nz1 = cos(alpha);
        float nx2 = sin(nextAlpha);
        float nz2 = cos(nextAlpha);

        // Coordenadas UV
        float u1 = alpha / (2 * M_PI);
        float u2 = nextAlpha / (2 * M_PI);
        float v_top = 1.0f;
        float v_bottom = 0.0f;

        float u_center = 0.5f;
        float v_center = 0.5f;
        float u1_base = 0.5f + 0.5f * sin(alpha);
        float v1_base = 0.5f + 0.5f * cos(alpha);
        float u2_base = 0.5f + 0.5f * sin(nextAlpha);
        float v2_base = 0.5f + 0.5f * cos(nextAlpha);

        // Base de baixo
        buffers.addTriangle(0.0f, h_baixo, 0.0f, x2, h_baixo, z2, x1, h_baixo, z1);
        buffers.addNormals(0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f);
        buffers.addTextureCoordinates(u_center, v_center, u2_base, v2_base, u1_base, v1_base);

        // Base de cima
        buffers.addTriangle(x2, h_cima, z2, 0.0f, h_cima, 0.0f, x1, h_cima, z1);
        buffers.addNormals(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        buffers.addTextureCoordinates(u2_base, v2_base, u_center, v_center, u1_base, v1_base);

        // Superfície lateral (2 triângulos)
        buffers.addTriangle(x2, h_cima, z2, x1, h_cima, z1, x1, h_baixo, z1);
        buffers.addNormals(nx2, 0.0f, nz2, nx1, 0.0f, nz1, nx1, 0.0f, nz1);
        buffers.addTextureCoordinates(u2, v_top, u1, v_top, u1, v_bottom);

        buffers.addTriangle(x2, h_baixo, z2, x2, h_cima, z2, x1, h_baixo, z1);
        buffers.addNormals(nx2, 0.0f, nz2, nx2, 0.0f, nz2, nx1, 0.0f, nz1);
        buffers.addTextureCoordinates(u2, v_bottom, u2, v_top, u1, v_bottom);
    
    }

    // Calcular centro e raio a partir dos vértices gerados
    vector<float> verts = buffers.getVertices();
    int totalVertices = (int)verts.size() / 3;
    if (totalVertices > 0) {
        float cx = 0.0f, cy = 0.0f, cz = 0.0f;
        for (size_t i = 0; i < verts.size(); i += 3) {
            cx += verts[i];
            cy += verts[i + 1];
            cz += verts[i + 2];
        }
        cx /= totalVertices; cy /= totalVertices; cz /= totalVertices;
        buffers.setCenter(cx, cy, cz);

        buffers.setRaioEsfera(sqrt(radius*radius + (height/2)*(height/2))); // raio da esfera circunscrita ao cilindro
    }

    return buffers;
}
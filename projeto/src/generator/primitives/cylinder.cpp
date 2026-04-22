#include "generator/primitives/cylinder.hpp"

PrimitiveBuffers generateCylinder(float radius, float height, int slices){
    PrimitiveBuffers buffers = PrimitiveBuffers();

    // Delta alpha
	float delta_alpha = 2*M_PI/slices;

	for(int i = 0; i < slices; i++){

		// Angulo alpha
		float alpha = i * delta_alpha;
		float nextAplha = (i+1) * delta_alpha ;

		// Posições
		float x1 = sin(alpha) * radius;     // Posição x do ponto atual
		float x2 = sin(nextAplha) * radius; // Posição x do próximo ponto

		float z1 = cos(alpha) * radius;     // Posição z do ponto atual
		float z2 = cos(nextAplha) * radius; // Posição z do próximo ponto

		// Alturas
		float h_cima = height/2;       // Altura da base de cima
		float h_baixo = -height/2;     // Altura da base de baixo

        // Adicionar triângulos
        // Base de baixo
        buffers.addTriangle(0.0f, h_baixo, 0.0f, x2, h_baixo, z2, x1, h_baixo, z1);
        // Base de cima
        buffers.addTriangle(x2, h_cima, z2, 0.0f, h_cima, 0.0f, x1, h_cima, z1);
        // Triângulo esquerda
        buffers.addTriangle(x2, h_cima, z2, x1, h_cima, z1, x1, h_baixo, z1);
        // Triângulo direita
        buffers.addTriangle(x2, h_baixo, z2, x2, h_cima, z2, x1, h_baixo, z1);
    }
    
    return buffers;
}
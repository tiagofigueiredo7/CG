#include "generator/primitives.hpp"
using namespace std;
using namespace utils;

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

			addTriangle(vertices, x1, 0, z1, x2, 0, z1, x2, 0, z2);
			addTriangle(vertices, x1, 0, z1, x2, 0, z2, x1, 0, z2);
		} 
	} 
	return vertices;
}

// Depois alterar generateBox para usar generatePlane? Código mais limpo

// Cria os vértices de uma caixa/cubo
vector <float> generateBox(float length, int divisions) {
	vector <float> vertices;
	float half = length / 2.0f;
	float divlength = length / divisions;

	// faces do plano XZ
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			float x1 = (j * divlength) - half;
			float x2 = x1 + divlength;
			float y1 = half;
			float y2 = -half;
			float z1 = (i * divlength) - half;
			float z2 = z1 + divlength;

			// plano "de cima"
			addTriangle(vertices, x1, y1, z1, x2, y1, z1, x2, y1, z2);
			addTriangle(vertices, x1, y1, z1, x2, y1, z2, x1, y1, z2);

			// plano "de baixo"
			addTriangle(vertices, x1, y2, z1, x2, y2, z1, x2, y2, z2);
			addTriangle(vertices, x1, y2, z1, x2, y2, z2, x1, y2, z2);
		}
	}

	// faces do plano XY
	for (int i = 0; i < divisions; i++) {
		for(int j = 0; j < divisions; j++) {
			float x1 = (j * divlength) - half;
			float x2 = x1 + divlength;
			float y1 = (i * divlength) - half;
			float y2 = y1 + divlength;
			float z1 = half;
			float z2 = -half;

			// plano "da frente"
			addTriangle(vertices, x1, y1, z1, x2, y1, z1, x2, y2, z1);
			addTriangle(vertices, x1, y1, z1, x2, y2, z1, x1, y2, z1);

			// plano "de trás"
			addTriangle(vertices, x1, y1, z2, x2, y1, z2, x2, y2, z2);
			addTriangle(vertices, x1, y1, z2, x2, y2, z2, x1, y2, z2);
		}
	}

	// faces do plano YZ
	for (int i = 0; i < divisions; i++) {
		for(int j = 0; j < divisions; j++) {
			float x1 = half;
			float x2 = -half;
			float y1 = (i * divlength) - half;
			float y2 = y1 + divlength;
			float z1 = (j * divlength) - half;
			float z2 = z1 + divlength;

			// plano "da direita"
			addTriangle(vertices, x1, y1, z1, x1, y1, z2, x1, y2, z2);
			addTriangle(vertices, x1, y1, z1, x1, y2, z2, x1, y2, z1);

			// plano "da esquerda"
			addTriangle(vertices, x2, y1, z1, x2, y1, z2, x2, y2, z2);
			addTriangle(vertices, x2, y1, z1, x2, y2, z2, x2, y2, z1);
		}
	}

	return vertices;
}

// Cria os vértices de uma esfera
vector <float> generateSphere(float radius, int slices, int stacks) {
	return vector <float>();
}

// Cria os vértices de um cone
vector <float> generateCone(float radius, float height, int slices, int stacks) {
	return vector <float>();
}
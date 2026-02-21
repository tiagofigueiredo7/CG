#include "generator/primitives.hpp"

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
            float z1 = (i * divlength) - half;
            float z2 = z1 + divlength;
            float y1 = half;
            float y2 = -half;

            // plano "de cima"
            addTriangle(vertices, x1, y1, z1, x2, y1, z2, x2, y1, z1);
            addTriangle(vertices, x1, y1, z1, x1, y1, z2, x2, y1, z2);

            // plano "de baixo"
            addTriangle(vertices, x1, y2, z1, x2, y2, z1, x2, y2, z2);
            addTriangle(vertices, x1, y2, z1, x2, y2, z2, x1, y2, z2);
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
            addTriangle(vertices, x1, y1, z1, x2, y2, z1, x2, y1, z1);
            addTriangle(vertices, x1, y1, z1, x1, y2, z1, x2, y2, z1);

            // plano "de trás"
            addTriangle(vertices, x1, y1, z2, x2, y1, z2, x2, y2, z2);
            addTriangle(vertices, x1, y1, z2, x2, y2, z2, x1, y2, z2);
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
            addTriangle(vertices, x1, y1, z1, x1, y2, z2, x1, y1, z2);
            addTriangle(vertices, x1, y1, z1, x1, y2, z1, x1, y2, z2);

            // plano "da esquerda"
            addTriangle(vertices, x2, y1, z1, x2, y1, z2, x2, y2, z2);
            addTriangle(vertices, x2, y1, z1, x2, y2, z2, x2, y2, z1);
        }
    }

    return vertices;
}


vector <float> generateSphere(float radius, int slices, int stacks){
	vector <float> vertices;

	float a = 2*M_PI/slices;
	float b = M_PI/stacks;

	for (int i = 0; i < stacks; i++) {

		float b1 = M_PI/2 - i * b;
        	float b2 = M_PI/2 - (i+1) * b;

		for (int j = 0 ; j <= slices ; j++ ){

			float a1 = j * a;
			float a2 = (j + 1) * a;

			// CANTO SUPERIOR ESQUERDO
			float x1 = radius * cos(b1) * sin(a1);
			float y1 = radius * sin(b1);
			float z1 = radius * cos(b1) * cos(a1);

			// CANTO SUPERIOR DIREITO
			float x2 = radius * cos(b1) * sin(a2);
			float y2 = radius * sin(b1);
			float z2 = radius * cos(b1) * cos(a2);

			// CANTO INFERIOR ESQUERDO
			float x3 = radius * cos(b2) * sin(a1);
			float y3 = radius * sin(b2);
			float z3 = radius * cos(b2) * cos(a1);

			// CANTO INFERIOR DIREITO
			float x4 = radius * cos(b2) * sin(a2);
			float y4 = radius * sin(b2);
			float z4 = radius * cos(b2) * cos(a2);

			if (i == 0) {
				// Polo superior
				addTriangle(vertices, x1, y1, z1, x3, y3, z3, x4, y4, z4);
			} 
			else if (i == stacks - 1) {
				// Polo inferior
				addTriangle(vertices, x2, y2, z2, x1, y1, z1, x3, y3, z3);
			} 
			else {
				// Parte média
				addTriangle(vertices, x1, y1, z1, x3, y3, z3, x4, y4, z4);
				addTriangle(vertices, x1, y1, z1, x4, y4, z4, x2, y2, z2);
			}
		}
	}

	return vertices;
}

// Cria os vértices de um cone
vector <float> generateCone(float radius, float height, int slices, int stacks) {
	vector <float> vertices;

	float a = 2*M_PI/slices;
	float b = height/stacks;

	for (int l = 0 ; l < slices ; l++){

		float a1 = a * l;
		float a2 = a * (l+1);

		float x1 = radius * cos(a1);
		float y1 = 0;
		float z1 = radius * sin(a1);

		float x2 = radius * cos(a2);
		float y2 = 0;
		float z2 = radius * sin(a2);

		addTriangle(vertices, x1, y1, z1, x2, y2, z2, 0.0, 0.0, 0.0);
	}

	for (int i = 0 ; i < stacks ; i++ ){

		float b1 = i * b;
	   	float b2 = (i+1) * b;

		float r1 = radius * (height - b1) / height;
		float r2 = radius * (height - b2) / height;

		for (int j = 0 ; j < slices ; j++ ){

			float a1 = j * a;
			float a2 = (j + 1) * a;

			float x1 = r1 * cos(a1);
			float y1 = b1;
			float z1 = r1 * sin(a1);

			float x2 = r1 * cos(a2);
			float y2 = b1;
			float z2 = r1 * sin(a2);

			float x3 = r2 * cos(a1);
			float y3 = b2;
			float z3 = r2 * sin(a1);

			float x4 = r2 * cos(a2);
			float y4 = b2;
			float z4 = r2 * sin(a2);

			addTriangle(vertices, x1, y1, z1, x3, y3, z3, x4, y4, z4);
			addTriangle(vertices, x1, y1, z1, x4, y4, z4, x2, y2, z2);
		}
	}
	return vertices;
}
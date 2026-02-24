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
			addTriangle(vertices, x1, y1, z2, x1, y2, z2, x2, y2, z2);
			addTriangle(vertices, x1, y1, z2, x2, y2, z2, x2, y1, z2);
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

	float aStep = 2 * M_PI / slices;
	float bStep = M_PI / stacks;

	float x_top = 0.0f;
	float y_top = radius;
	float z_top = 0.0f;

	float b_top = M_PI/2 - bStep;

	for (int j = 0; j < slices; j++) {
		float a = j * aStep;
		float a1 = (j + 1) * aStep;

		float x1 = radius * cos(b_top) * sin(a);
		float y1 = radius * sin(b_top);
		float z1 = radius * cos(b_top) * cos(a);

		float x2 = radius * cos(b_top) * sin(a1);
		float y2 = radius * sin(b_top);
		float z2 = radius * cos(b_top) * cos(a1);

		addTriangle(vertices, x_top, y_top, z_top, x1, y1, z1, x2, y2, z2);
	}

	for (int i = 1; i < stacks - 1; i++) {
		float b = M_PI/2 - (i * bStep);
		float b1 = M_PI/2 - ((i + 1) * bStep);

		for (int j = 0; j < slices; j++) {
			float a = j * aStep;
			float a1 = (j + 1) * aStep;

			float x1 = radius * cos(b) * sin(a);
			float y1 = radius * sin(b);
			float z1 = radius * cos(b) * cos(a);

			float x2 = radius * cos(b) * sin(a1);
			float y2 = radius * sin(b);
			float z2 = radius * cos(b) * cos(a1);

			float x3 = radius * cos(b1) * sin(a);
			float y3 = radius * sin(b1);
			float z3 = radius * cos(b1) * cos(a);

			float x4 = radius * cos(b1) * sin(a1);
			float y4 = radius * sin(b1);
			float z4 = radius * cos(b1) * cos(a1);

			addTriangle(vertices, x1, y1, z1, x3, y3, z3, x2, y2, z2);
			addTriangle(vertices, x2, y2, z2, x3, y3, z3, x4, y4, z4);
		}
	}

	float x_bottom = 0.0f;
	float y_bottom = -radius;
	float z_bottom = 0.0f;

	float b_bottom = -M_PI/2 + bStep;

	for (int j = 0; j < slices; j++) {
		float a = j * aStep;
		float a1 = (j + 1) * aStep;

		float x1 = radius * cos(b_bottom) * sin(a);
		float y1 = radius * sin(b_bottom);
		float z1 = radius * cos(b_bottom) * cos(a);

		float x2 = radius * cos(b_bottom) * sin(a1);
		float y2 = radius * sin(b_bottom);
		float z2 = radius * cos(b_bottom) * cos(a1);

		addTriangle(vertices, x_bottom, y_bottom, z_bottom, x2, y2, z2, x1, y1, z1);
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
#include "generator/primitives/cone.hpp"

// Cria os vértices de um cone
PrimitiveBuffers generateCone(float radius, float height, int slices, int stacks) {
	PrimitiveBuffers buffers = PrimitiveBuffers();

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

		float u1 = 0.5f + 0.5f * cos(a1);
		float v1 = 0.5f + 0.5f * sin(a1);
		float u2 = 0.5f + 0.5f * cos(a2);
		float v2 = 0.5f + 0.5f * sin(a2);

		buffers.addTriangle(x1, y1, z1, x2, y2, z2, 0.0, 0.0, 0.0);
		buffers.addTextureCoordinates(u1, v1, u2, v2, 0.5f, 0.5f);
		buffers.addNormals(0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0);
	}

	for (int i = 0 ; i < stacks ; i++ ){

		float b1 = i * b;
	   	float b2 = (i+1) * b;

		float r1 = radius * (height - b1) / height;
		float r2 = radius * (height - b2) / height;

		for (int j = 0 ; j < slices ; j++ ){

			// Vértices
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

			// Normais para cada vértice
			float n1[3] = {x1, radius / height, z1};
			float n2[3] = {x2, radius / height, z2};
			float n3[3] = {x3, radius / height, z3};
			float n4[3] = {x4, radius / height, z4};
			normalize(n1);
			normalize(n2);
			normalize(n3);
			normalize(n4);

			// Coordenadas de textura
			float u1 = a1 / (2 * M_PI);
			float u2 = a2 / (2 * M_PI);

			float v1 = b1 / height;
			float v2 = b2 / height;

			buffers.addTriangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);
			buffers.addTextureCoordinates(u1, v1, u1, v2, u2, v2);
			buffers.addNormals(n1[0], n1[1], n1[2], n3[0], n3[1], n3[2], n4[0], n4[1], n4[2]);


			buffers.addTriangle(x1, y1, z1, x4, y4, z4, x2, y2, z2);
			buffers.addTextureCoordinates(u1, v1, u2, v2, u2, v1);
			buffers.addNormals(n1[0], n1[1], n1[2], n4[0], n4[1], n4[2], n2[0], n2[1], n2[2]);
		}
	}
	return buffers;
}

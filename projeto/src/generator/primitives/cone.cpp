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

		buffers.addTriangle(x1, y1, z1, x2, y2, z2, 0.0, 0.0, 0.0);
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

			buffers.addTriangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);
			buffers.addTriangle(x1, y1, z1, x4, y4, z4, x2, y2, z2);
		}
	}
	return buffers;
}

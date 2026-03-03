#include "generator/primitives/sphere.hpp"

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

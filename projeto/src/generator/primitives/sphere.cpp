#include "generator/primitives/sphere.hpp"

PrimitiveBuffers generateSphere(float radius, int slices, int stacks){
	PrimitiveBuffers buffers = PrimitiveBuffers();

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


		float u1 = a / (2 * M_PI);
		float u2 = a1 / (2 * M_PI);
		
		// V é constante no topo (v = 0 ou 1)
		float v_top = 0.0f;  // ou 1.0f dependendo da orientação
		float v1 = (M_PI/2 - (M_PI/2 - bStep)) / M_PI;


		buffers.addTriangle(x_top, y_top, z_top, x1, y1, z1, x2, y2, z2);
		buffers.addNormals(x_top/radius, y_top/radius, z_top/radius, x1/radius, y1/radius, z1/radius, x2/radius, y2/radius, z2/radius);
		buffers.addTextureCoordinates(u1, v_top, u1, v1, u2, v1);
	}

	for (int i = 1; i < stacks - 1; i++) {
		float b = M_PI/2 - (i * bStep);
		float b1 = M_PI/2 - ((i + 1) * bStep);

		float v = (M_PI/2 - b) / M_PI;
    	float v1 = (M_PI/2 - b1) / M_PI;

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


			float u = a / (2 * M_PI);
        	float u1 = a1 / (2 * M_PI);

			buffers.addTriangle(x1, y1, z1, x3, y3, z3, x2, y2, z2);
			buffers.addNormals(x1/radius, y1/radius, z1/radius, x3/radius, y3/radius, z3/radius, x2/radius, y2/radius, z2/radius);
			buffers.addTextureCoordinates(u, v, u, v1, u1, v); 

			buffers.addTriangle(x2, y2, z2, x3, y3, z3, x4, y4, z4);
			buffers.addNormals(x2/radius, y2/radius, z2/radius, x3/radius, y3/radius, z3/radius, x4/radius, y4/radius, z4/radius);
			buffers.addTextureCoordinates(u1, v, u, v1, u1, v1);
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


		float u = a / (2 * M_PI);
		float u1 = a1 / (2 * M_PI);
		
		// Para a base, v vai de 0.5 (equador) até 1.0 (pólo sul)
		float v_bottom = (M_PI/2 - b_bottom) / M_PI;
		float v_surface = (M_PI/2 - (b_bottom + bStep)) / M_PI;  // um pouco acima da base

		buffers.addTriangle(x_bottom, y_bottom, z_bottom, x2, y2, z2, x1, y1, z1);
		buffers.addNormals(x_bottom/radius, y_bottom/radius, z_bottom/radius, x2/radius, y2/radius, z2/radius, x1/radius, y1/radius, z1/radius);
		buffers.addTextureCoordinates(u, v_bottom, u1, v_bottom, u, v_surface);
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

		buffers.setRaioEsfera(radius); // o raio da esfera é o próprio raio fornecido
	}

	return buffers;
}

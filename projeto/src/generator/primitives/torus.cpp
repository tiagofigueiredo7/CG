#include "generator/primitives/torus.hpp"

PrimitiveBuffers generateTorus(float majorRadius, float minorRadius, int slices, int stacks){
    PrimitiveBuffers buffers = PrimitiveBuffers();

    float delta_theta = 2*M_PI/slices;	//angulo do cículo externo (maior)
	float delta_phi = 2*M_PI/stacks;	//angulo do círculo interno (menor - dentro do tubo)

	//vamos desenhar por fatias (slices)
    for(int i = 0; i < slices; i++){
        float theta = i*delta_theta;
        float nextTheta = (i+1)*delta_theta;

        float u1 = theta / (2*M_PI); // Horizontal
        float u2 = nextTheta / (2*M_PI);

        for(int j = 0; j < stacks; j++){
            float phi = j*delta_phi;
            float nextPhi = (j+1)*delta_phi;

            float v1 = phi / (2*M_PI);
            float v2 = nextPhi / (2*M_PI);

            //definição dos pontos do quadrado
            // 		t    nt
            //	p	P1---P3
            //		|	 |
            // 	np	P2---P4

            // Definição da normal para cada vértice : n = (cos(theta)*cos(phi), sin(phi), sin(theta)*cos(phi))

            //P1
            float x1 = (majorRadius + minorRadius*cos(phi))*cos(theta);
            float y1 = minorRadius*sin(phi);
            float z1 = (majorRadius + minorRadius*cos(phi))*sin(theta);

            float nx1 = cos(phi)*cos(theta);
            float ny1 = sin(phi);
            float nz1 = cos(phi)*sin(theta);

            //P2
            float x2 = (majorRadius + minorRadius*cos(nextPhi))*cos(theta);
            float y2 = minorRadius*sin(nextPhi);
            float z2 = (majorRadius + minorRadius*cos(nextPhi))*sin(theta);

            float nx2 = cos(nextPhi)*cos(theta);
            float ny2 = sin(nextPhi);
            float nz2 = cos(nextPhi)*sin(theta);

            //P3
            float x3 = (majorRadius + minorRadius*cos(phi))*cos(nextTheta);
            float y3 = minorRadius*sin(phi);
            float z3 = (majorRadius + minorRadius*cos(phi))*sin(nextTheta);

            float nx3 = cos(phi)*cos(nextTheta);
            float ny3 = sin(phi);
            float nz3 = cos(phi)*sin(nextTheta);

            //P4
            float x4 = (majorRadius + minorRadius*cos(nextPhi))*cos(nextTheta);
            float y4 = minorRadius*sin(nextPhi);
            float z4 = (majorRadius + minorRadius*cos(nextPhi))*sin(nextTheta);

            float nx4 = cos(nextPhi)*cos(nextTheta);
            float ny4 = sin(nextPhi);
            float nz4 = cos(nextPhi)*sin(nextTheta);
            



            buffers.addTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
            buffers.addNormals(nx1, ny1, nz1, nx2, ny2, nz2, nx3, ny3, nz3);
            buffers.addTextureCoordinates(u1,v1,u1,v2,u2,v1);

            buffers.addTriangle(x3, y3, z3, x2, y2, z2, x4, y4, z4);
            buffers.addNormals(nx3, ny3, nz3, nx2, ny2, nz2, nx4, ny4, nz4);
            buffers.addTextureCoordinates(u2,v1,u1,v2,u2,v2);

        }
    }

    // Calcular centro e raio a partir dos vértices gerados
    vector<float> verts = buffers.getVertices();
    int totalVertices = (int)verts.size() / 3;
    if (totalVertices > 0) {
        buffers.setCenter(0, 0, 0); // centro do toro é a origem
        buffers.setRaioEsfera(majorRadius + minorRadius); // raio da esfera circunscrita ao toro é a soma dos raios maior e menor
    }

    return buffers;
}
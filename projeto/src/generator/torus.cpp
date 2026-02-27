#include "generator/torus.hpp"

vector <float> generateTorus(float majorRadius, float minorRadius, int slices, int stacks){
    vector<float> vertices;

    float delta_theta = 2*M_PI/slices;	//angulo do cículo externo (maior)
	float delta_phi = 2*M_PI/stacks;	//angulo do círculo interno (menor - dentro do tubo)

	//vamos desenhar por fatias (slices)
    for(int i = 0; i < slices; i++){
        float theta = i*delta_theta;
        float nextTheta = (i+1)*delta_theta;

        for(int j = 0; j < stacks; j++){
            float phi = j*delta_phi;
            float nextPhi = (j+1)*delta_phi;

            //definição dos pontos do quadrado
            // 		t    nt
            //	p	P1---P3
            //		|	 |
            // 	np	P2---P4

            //P1
            float x1 = (majorRadius + minorRadius*cos(phi))*cos(theta);
            float y1 = minorRadius*sin(phi);
            float z1 = (majorRadius + minorRadius*cos(phi))*sin(theta);

            //P2
            float x2 = (majorRadius + minorRadius*cos(nextPhi))*cos(theta);
            float y2 = minorRadius*sin(nextPhi);
            float z2 = (majorRadius + minorRadius*cos(nextPhi))*sin(theta);

            //P3
            float x3 = (majorRadius + minorRadius*cos(phi))*cos(nextTheta);
            float y3 = minorRadius*sin(phi);
            float z3 = (majorRadius + minorRadius*cos(phi))*sin(nextTheta);

            //P4
            float x4 = (majorRadius + minorRadius*cos(nextPhi))*cos(nextTheta);
            float y4 = minorRadius*sin(nextPhi);
            float z4 = (majorRadius + minorRadius*cos(nextPhi))*sin(nextTheta);

            addTriangle(vertices, x1, y1, z1, x2, y2, z2, x3, y3, z3);
            addTriangle(vertices, x3, y3, z3, x2, y2, z2, x4, y4, z4);
        }
    }
    
    return vertices;
}
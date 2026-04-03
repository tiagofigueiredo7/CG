#include "generator/primitives/noiseSphere.hpp"

float noise(float u, float v, float amplitude){
    float x = cos(v) * sin(u);
    float y = sin(v);
    float z = cos(v) * cos(u);

    float n = sin((x * 12.9898f + y * 78.233f + z * 37.719f) + 19.19f) *
                cos((x * 93.989f  - y * 67.345f + z * 54.123f) - 11.73f);

    return amplitude * 0.1f * n;
}


vector <float> generateNoiseSphere(float radius, int slices, int stacks, float amplitude){
    
    vector<float> vertices;
    Point3D grid[stacks+1][slices+1];
    float u=0,v=0,r=0;

    for (int i=0; i<=stacks; i++) {
        v = -M_PI/2 + i*(M_PI/stacks);

        for (int j=0; j<=slices; j++) {
            u = j*(2*M_PI/slices);

            r = radius + noise(u,v,amplitude);

            grid[i][j].x = r*cos(v)*sin(u);
            grid[i][j].y = r*sin(v);
            grid[i][j].z = r*cos(v)*cos(u);
        }
    }

    for (int i=0; i<stacks;i++){
        for (int j=0; j<slices;j++){
            Point3D A = grid[i][j];
            Point3D B = grid[i][j+1];
            Point3D C = grid[i+1][j];
            Point3D D = grid[i+1][j+1];

            addTriangle(vertices, A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
            addTriangle(vertices, C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
        }
    }

    return vertices;
}
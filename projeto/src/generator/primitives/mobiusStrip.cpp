#include "generator/primitives/mobiusStrip.hpp"

vector <float> generateMobiusStrip(float radius, float width, int slices){

    vector<float> vertices;

    Point3D grid[slices+1][2];
    float u=0, v=0;

    for (int i=0; i<= slices; i++){
        u = i * ((2*M_PI)/slices);

        for (int j=0; j<2; j++){
            v = -width + j*(2*width);
            grid[i][j].x = (radius + v*cos(u/2)) * cos(u);
            grid[i][j].y = (radius + v*cos(u/2)) * sin(u);
            grid[i][j].z = v * sin(u/2);
        }
    }

    for (int i=0; i<slices; i++) {
        Point3D A, B, C, D;
        if (i == slices - 1) {//Caso especial da torsão da fita
            A = grid[i][0];
            B = grid[i][1];
            C = grid[0][1];
            D = grid[0][0];
        } else {
            A = grid[i][0];
            B = grid[i][1];
            C = grid[i+1][0];
            D = grid[i+1][1];
        }

        // Cada triangulo é adicionado 2 vezes porque a figura é não orientável
        addTriangle(vertices, A.x, A.y, A.z, C.x, C.y, C.z, B.x, B.y, B.z);
        addTriangle(vertices, B.x, B.y, B.z, C.x, C.y, C.z, D.x, D.y, D.z);

        addTriangle(vertices, A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
        addTriangle(vertices, C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
}

    return vertices;

}
#include "generator/primitives/kleinBottle.hpp"

PrimitiveBuffers generateKleinBottle(float radius, int slices, int stacks) {

    PrimitiveBuffers buffers = PrimitiveBuffers();
    Point3D grid[stacks+1][slices+1];
    float u=0,v=0;

    for (int i=0; i<=stacks; i++) {
        u = i*(2*M_PI/stacks);

        for (int j=0; j<=slices; j++) {
            v = j*(2*M_PI/slices);

            if (u<M_PI) {
                grid[i][j].x = 3*cos(u)*(1+sin(u)) + (2*(1-cos(u)/2))*cos(u)*cos(v);
                grid[i][j].y = 8*sin(u) + (2*(1-cos(u)/2))*sin(u)*cos(v);
                grid[i][j].z = (2*(1-cos(u)/2))*sin(v);
            } else {
                grid[i][j].x = 3*cos(u)*(1+sin(u)) + (2*(1-cos(u)/2))*cos(v+M_PI);
                grid[i][j].y = 8*sin(u);
                grid[i][j].z = (2*(1-cos(u)/2))*sin(v);
            }

        }
    }

    for (int i=0; i<stacks;i++){
        for (int j=0; j<slices;j++){
            Point3D A = grid[i][j];
            Point3D B = grid[i][j+1];
            Point3D C = grid[i+1][j];
            Point3D D = grid[i+1][j+1];

            // Cada triangulo é adicionado 2 vezes porque a figura é não orientável
            buffers.addTriangle( A.x, A.y, A.z, C.x, C.y, C.z, B.x, B.y, B.z);
            buffers.addTriangle(B.x, B.y, B.z, C.x, C.y, C.z, D.x, D.y, D.z);

            buffers.addTriangle(A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
            buffers.addTriangle(C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
        }
    }

    

    return buffers;
}
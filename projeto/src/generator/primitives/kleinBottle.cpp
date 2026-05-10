#include "generator/primitives/kleinBottle.hpp"

PrimitiveBuffers generateKleinBottle(int slices, int stacks) {

    PrimitiveBuffers buffers = PrimitiveBuffers();

    Point3D grid[slices+1][stacks+1];
    Point3D normais[slices+1][stacks+1];
    float u=0, v=0, u_text=0, v_text=0;

    float u_text_grid[slices+1][stacks+1];
    float v_text_grid[slices+1][stacks+1];

    for (int i=0; i<=slices; i++) {
        u = i*(2*M_PI/slices);

        u_text = u / (2*M_PI); // Coordenada horizontal da textura normalizada

        for (int j=0; j<=stacks; j++) {
            v = j*(2*M_PI/stacks);

            v_text = v / (2*M_PI); // Coordenada vertical da textura normalizada

            float du_x, du_y, du_z, dv_x, dv_y, dv_z;

            if (u<M_PI) {
                grid[i][j].x = 3*cos(u)*(1+sin(u)) + (2*(1-cos(u)/2))*cos(u)*cos(v);
                grid[i][j].y = 8*sin(u) + (2*(1-cos(u)/2))*sin(u)*cos(v);
                grid[i][j].z = (2*(1-cos(u)/2))*sin(v);

                
                // Nota: 2*(1 - cos(u)/2) = 2 - cos(u)
                du_x = -3*sin(u)*(1+sin(u)) + 3*cos(u)*cos(u)
                       + sin(u)*cos(u)*cos(v) - (2 - cos(u))*sin(u)*cos(v);
                du_y = 8*cos(u) + (sin(u)*sin(u))*cos(v) + (2 - cos(u))*cos(u)*cos(v);
                du_z = sin(u)*sin(v);

                dv_x = - (2 - cos(u)) * cos(u) * sin(v);
                dv_y = - (2 - cos(u)) * sin(u) * sin(v);
                dv_z = (2 - cos(u)) * cos(v);

            } else {
                grid[i][j].x = 3*cos(u)*(1+sin(u)) + (2*(1-cos(u)/2))*cos(v+M_PI);
                grid[i][j].y = 8*sin(u);
                grid[i][j].z = (2*(1-cos(u)/2))*sin(v);


                du_x = -3*sin(u)*(1+sin(u)) + 3*cos(u)*cos(u) - sin(u)*cos(v);
                du_y = 8*cos(u);
                du_z = sin(u)*sin(v);

                dv_x = (2 - cos(u)) * sin(v);
                dv_y = 0.0f;
                dv_z = (2 - cos(u)) * cos(v);
            }

            // Produto vetorial: n = du × dv
            float nx = du_y*dv_z - du_z*dv_y;
            float ny = du_z*dv_x - du_x*dv_z;
            float nz = du_x*dv_y - du_y*dv_x;

            // Normalizar
            float length = sqrt(nx*nx + ny*ny + nz*nz);
            nx /= length;
            ny /= length;
            nz /= length;

            // Garantir orientação consistente: apontar para fora (aprox. em relação à origem)
            float dot = nx * grid[i][j].x + ny * grid[i][j].y + nz * grid[i][j].z;
            if (dot < 0.0f) {
                nx = -nx; ny = -ny; nz = -nz;
            }

            normais[i][j].x = nx;
            normais[i][j].y = ny;
            normais[i][j].z = nz;

            // Armazenar as coordenadas de textura para cada vértice
            u_text_grid[i][j] = u_text;
            v_text_grid[i][j] = v_text;

        }
    }

    for (int i=0; i<slices;i++){
        float uA, vA, uB, vB, uC, vC, uD, vD;
        float Anx, Any, Anz, Bnx, Bny, Bnz, Cnx, Cny, Cnz, Dnx, Dny, Dnz;
        for (int j=0; j<stacks;j++){
            Point3D A = grid[i][j]; uA = u_text_grid[i][j]; vA = v_text_grid[i][j]; Anx = normais[i][j].x; Any = normais[i][j].y; Anz = normais[i][j].z;
            Point3D B = grid[i][j+1]; uB = u_text_grid[i][j+1]; vB = v_text_grid[i][j+1]; Bnx = normais[i][j+1].x; Bny = normais[i][j+1].y; Bnz = normais[i][j+1].z;
            Point3D C = grid[i+1][j]; uC = u_text_grid[i+1][j]; vC = v_text_grid[i+1][j]; Cnx = normais[i+1][j].x; Cny = normais[i+1][j].y; Cnz = normais[i+1][j].z;
            Point3D D = grid[i+1][j+1]; uD = u_text_grid[i+1][j+1]; vD = v_text_grid[i+1][j+1]; Dnx = normais[i+1][j+1].x; Dny = normais[i+1][j+1].y; Dnz = normais[i+1][j+1].z;

            
            // Cada triangulo é adicionado 2 vezes porque a figura é não orientável
            buffers.addTriangle( A.x, A.y, A.z, C.x, C.y, C.z, B.x, B.y, B.z);
            buffers.addNormals(Anx, Any, Anz, Cnx, Cny, Cnz, Bnx, Bny, Bnz);
            buffers.addTextureCoordinates(uA, vA, uC, vC, uB, vB);

            buffers.addTriangle(B.x, B.y, B.z, C.x, C.y, C.z, D.x, D.y, D.z);   
            buffers.addNormals(Bnx, Bny, Bnz, Cnx, Cny, Cnz, Dnx, Dny, Dnz);
            buffers.addTextureCoordinates(uB, vB, uC, vC, uD, vD);



            buffers.addTriangle(A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
            buffers.addNormals(Anx, Any, Anz, Bnx, Bny, Bnz, Cnx, Cny, Cnz);
            buffers.addTextureCoordinates(uA, vA, uB, vB, uC, vC);

            buffers.addTriangle(C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
            buffers.addNormals(Cnx, Cny, Cnz, Bnx, Bny, Bnz, Dnx, Dny, Dnz);
            buffers.addTextureCoordinates(uC, vC, uB, vB, uD, vD);
        }
    }

    

    return buffers;
}
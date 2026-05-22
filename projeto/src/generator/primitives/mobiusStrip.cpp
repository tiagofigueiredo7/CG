#include "generator/primitives/mobiusStrip.hpp"

PrimitiveBuffers generateMobiusStrip(float radius, float width, int slices){

    PrimitiveBuffers buffers = PrimitiveBuffers();

    Point3D grid[slices+1][2];
    Point3D normais[slices+1][2];
    float u=0, v=0, u_text=0, v_text=0;

    float u_text_grid[slices+1][2];
    float v_text_grid[slices+1][2];

    for (int i=0; i<= slices; i++){
        u = i * ((2*M_PI)/slices);

        u_text = u / (2*M_PI); // Coordenada horizontal da textura normalizada

        for (int j=0; j<2; j++){
            v = -width + j*(2*width);

            v_text = (v + width) / (2*width); // Coordenada vertical da textura normalizada
            
            // Vértices
            grid[i][j].x = (radius + v*cos(u/2)) * cos(u);
            grid[i][j].y = (radius + v*cos(u/2)) * sin(u);
            grid[i][j].z = v * sin(u/2);

            // Armazenar as coordenadas de textura para cada vértice
            u_text_grid[i][j] = u_text;
            v_text_grid[i][j] = v_text;


            // Calcular derivadas parciais
            float du_x = -(radius + v*cos(u/2))*sin(u) + (v*sin(u/2)/2)*cos(u);
            float du_y = (radius + v*cos(u/2))*cos(u) - (v*sin(u/2)/2)*sin(u);
            float du_z = (v/2)*cos(u/2);

            float dv_x = cos(u/2)*cos(u);
            float dv_y = cos(u/2)*sin(u);
            float dv_z = sin(u/2);

            // Produto vetorial: n = du × dv
            float nx = du_y*dv_z - du_z*dv_y;
            float ny = du_z*dv_x - du_x*dv_z;
            float nz = du_x*dv_y - du_y*dv_x;

            // Normalizar
            float length = sqrt(nx*nx + ny*ny + nz*nz);
            nx /= length;
            ny /= length;
            nz /= length;

            normais[i][j].x = nx;
            normais[i][j].y = ny;
            normais[i][j].z = nz;


        }
    }

    for (int i=0; i<slices; i++) {
        Point3D A, B, C, D;
        float uA, vA, uB, vB, uC, vC, uD, vD;
        float Anx, Any, Anz, Bnx, Bny, Bnz, Cnx, Cny, Cnz, Dnx, Dny, Dnz;
        if (i == slices - 1) {//Caso especial da torsão da fita
            A = grid[i][0]; uA = u_text_grid[i][0]; vA = v_text_grid[i][0]; Anx = normais[i][0].x; Any = normais[i][0].y; Anz = normais[i][0].z;
            B = grid[i][1]; uB = u_text_grid[i][1]; vB = v_text_grid[i][1]; Bnx = normais[i][1].x; Bny = normais[i][1].y; Bnz = normais[i][1].z;
            C = grid[0][1]; uC = u_text_grid[0][1]; vC = v_text_grid[0][1]; Cnx = normais[0][1].x; Cny = normais[0][1].y; Cnz = normais[0][1].z;
            D = grid[0][0]; uD = u_text_grid[0][0]; vD = v_text_grid[0][0]; Dnx = normais[0][0].x; Dny = normais[0][0].y; Dnz = normais[0][0].z;
        } else {
            A = grid[i][0]; uA = u_text_grid[i][0]; vA = v_text_grid[i][0]; Anx = normais[i][0].x; Any = normais[i][0].y; Anz = normais[i][0].z;
            B = grid[i][1]; uB = u_text_grid[i][1]; vB = v_text_grid[i][1]; Bnx = normais[i][1].x; Bny = normais[i][1].y; Bnz = normais[i][1].z;
            C = grid[i+1][0]; uC = u_text_grid[i+1][0]; vC = v_text_grid[i+1][0]; Cnx = normais[i+1][0].x; Cny = normais[i+1][0].y; Cnz = normais[i+1][0].z;
            D = grid[i+1][1]; uD = u_text_grid[i+1][1]; vD = v_text_grid[i+1][1]; Dnx = normais[i+1][1].x; Dny = normais[i+1][1].y; Dnz = normais[i+1][1].z;
        }

        // Cada triangulo é adicionado 2 vezes porque a figura é não orientável
        buffers.addTriangle( A.x, A.y, A.z, C.x, C.y, C.z, B.x, B.y, B.z);
        buffers.addTextureCoordinates(uA, vA, uC, vC, uB, vB);
        buffers.addNormals(Anx, Any, Anz, Cnx, Cny, Cnz, Bnx, Bny, Bnz);

        buffers.addTriangle( B.x, B.y, B.z, C.x, C.y, C.z, D.x, D.y, D.z);
        buffers.addTextureCoordinates(uB, vB, uC, vC, uD, vD);
        buffers.addNormals(Bnx, Bny, Bnz, Cnx, Cny, Cnz, Dnx, Dny, Dnz);


        

        buffers.addTriangle( A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
        buffers.addTextureCoordinates(uA, vA, uB, vB, uC, vC);
        buffers.addNormals(Anx, Any, Anz, Bnx, Bny, Bnz, Cnx, Cny, Cnz);

        buffers.addTriangle( C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
        buffers.addTextureCoordinates(uC, vC, uB, vB, uD, vD);
        buffers.addNormals(Cnx, Cny, Cnz, Bnx, Bny, Bnz, Dnx, Dny, Dnz);
    }

    buffers.setRaioEsfera(radius + width); // A esfera circunscrita tem raio igual à distância máxima do centro, que é radius + width

    return buffers;
}
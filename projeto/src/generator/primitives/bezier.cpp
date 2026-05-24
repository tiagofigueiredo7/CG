#include "generator/primitives/bezier.hpp"

Point3D bezier(float u, float v, vector<float>* control_points){

    float B[4];
    float C[4];

    B[0] = (1 - u) * (1 - u) * (1 - u);
    B[1] = 3 * u * (1 - u) * (1 - u);
    B[2] = 3 * u * u * (1 - u);
    B[3] = u * u * u;

    C[0] = (1 - v) * (1 - v) * (1 - v);
    C[1] = 3 * v * (1 - v) * (1 - v);
    C[2] = 3 * v * v * (1 - v);
    C[3] = v * v * v;

    Point3D result = { .x = 0, .y = 0, .z = 0};

    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){

            float peso = B[i]*C[j];

            int pos = (i*4 + j)*3;

            result.x += (*control_points)[pos] * peso;
            result.y += (*control_points)[pos + 1] * peso;
            result.z += (*control_points)[pos + 2] * peso;
        }
    }

    return result;

}

Point3D bezierDerivadaU(float u, float v, vector<float>* control_points){

    float B[3];
    float C[4];

    B[0] = (1 - u) * (1 - u);
    B[1] = 2 * u * (1 - u);
    B[2] = u * u;

    C[0] = (1 - v) * (1 - v) * (1 - v);
    C[1] = 3 * v * (1 - v) * (1 - v);
    C[2] = 3 * v * v * (1 - v);
    C[3] = v * v * v;

    Point3D result = { .x = 0, .y = 0, .z = 0};

    for (int i=0; i<3; i++){
        for (int j=0; j<4; j++){

            float peso = 3.0f * B[i] * C[j];

            int pos = (i*4 + j)*3;
            int pos_next = ((i + 1)*4 + j)*3;

            result.x += ((*control_points)[pos_next] - (*control_points)[pos]) * peso;
            result.y += ((*control_points)[pos_next + 1] - (*control_points)[pos + 1]) * peso;
            result.z += ((*control_points)[pos_next + 2] - (*control_points)[pos + 2]) * peso;
        }
    }

    return result;

}

Point3D bezierDerivadaV(float u, float v, vector<float>* control_points){

    float B[4];
    float C[3];

    B[0] = (1 - u) * (1 - u) * (1 - u);
    B[1] = 3 * u * (1 - u) * (1 - u);
    B[2] = 3 * u * u * (1 - u);
    B[3] = u * u * u;

    C[0] = (1 - v) * (1 - v);
    C[1] = 2 * v * (1 - v);
    C[2] = v * v;

    Point3D result = { .x = 0, .y = 0, .z = 0};

    for (int i=0; i<4; i++){
        for (int j=0; j<3; j++){

            float peso = 3.0f * B[i] * C[j];

            int pos = (i*4 + j)*3;
            int pos_next = (i*4 + (j + 1))*3;

            result.x += ((*control_points)[pos_next] - (*control_points)[pos]) * peso;
            result.y += ((*control_points)[pos_next + 1] - (*control_points)[pos + 1]) * peso;
            result.z += ((*control_points)[pos_next + 2] - (*control_points)[pos + 2]) * peso;
        }
    }

    return result;

}

vector<float> getValores_in_Indices(vector<float>* indices, vector<float>* control_points){
    vector<float> result;
    for (float index : *indices){
        int id = (int)(index);
        result.push_back((*control_points)[id*3]);
        result.push_back((*control_points)[id*3 + 1]);
        result.push_back((*control_points)[id*3 + 2]);
    }
    return result;
}

PrimitiveBuffers generateBezierModel(char* file_path, int tesselation) {

    BezierPatch data = BezierPatch();
    data.parse_Patch_File(file_path);

    PrimitiveBuffers buffers = PrimitiveBuffers();

    int n_patches = data.getPatchesCount();
    vector<float> control_points_values = data.getControlPointsValues();

    // Delta usado na construção da matriz de aproximação
    float delta = 1.0f / tesselation;

    // Matriz (u,v) de aproximação da superficie
    float u[tesselation+1][tesselation+1];
    float v[tesselation+1][tesselation+1];    

    for (int i = 0; i < tesselation + 1; i++){
        for (int j = 0; j < tesselation + 1; j++){
            u[i][j] = i*delta;
            v[i][j] = j*delta;
        }
    } 

    for (int p = 0; p< n_patches; p++){

        // Pontos de controlo usados para definir a superficie
        vector<float> valores = getValores_in_Indices(data.getIndicesPatch(p),&control_points_values);

        // Matriz que vai conter os pontos usados para fazer os triangulos
        // Cada P(i,i) = u_v[i,j] + pontos de controlo
        Point3D superficie[tesselation+1][tesselation+1];
        Point3D derivadaU[tesselation+1][tesselation+1];
        Point3D derivadaV[tesselation+1][tesselation+1];

        for (int i = 0; i < tesselation + 1; i++){
            for (int j = 0; j < tesselation + 1; j++){
                superficie[i][j] = bezier(u[i][j],v[i][j],&valores);
                derivadaU[i][j] = bezierDerivadaU(u[i][j],v[i][j],&valores);
                derivadaV[i][j] = bezierDerivadaV(u[i][j],v[i][j],&valores);

            }
        }

        // É usado tesselation sem o +1, visto que ele vai ler 4 pontos/1 quadrado/2 triangulos de uma vez
        for (int i = 0; i < tesselation; i++){
            for (int j = 0; j < tesselation; j++){
                Point3D A = superficie[i][j]; Point3D A_devU = derivadaU[i][j]; Point3D A_devV = derivadaV[i][j];
                Point3D B = superficie[i][j+1]; Point3D B_devU = derivadaU[i][j+1]; Point3D B_devV = derivadaV[i][j+1];
                Point3D C = superficie[i+1][j]; Point3D C_devU = derivadaU[i+1][j]; Point3D C_devV = derivadaV[i+1][j];
                Point3D D = superficie[i+1][j+1]; Point3D D_devU = derivadaU[i+1][j+1]; Point3D D_devV = derivadaV[i+1][j+1];

                float A_u[3] = {A_devU.x, A_devU.y, A_devU.z};
                float A_v[3] = {A_devV.x, A_devV.y, A_devV.z};
                float normal1[3];
                cross(A_v, A_u, normal1);
                normalize(normal1);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal1[0]) || isnan(normal1[1]) || isnan(normal1[2])) {
                    normal1[0] = 0.0f;
                    normal1[1] = 1.0f;
                    normal1[2] = 0.0f;
                }

                float B_u[3] = {B_devU.x, B_devU.y, B_devU.z};
                float B_v[3] = {B_devV.x, B_devV.y, B_devV.z};
                float normal2[3];
                cross(B_v, B_u, normal2);
                normalize(normal2);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal2[0]) || isnan(normal2[1]) || isnan(normal2[2])) {
                    normal2[0] = 0.0f;
                    normal2[1] = 1.0f;
                    normal2[2] = 0.0f;
                }

                float C_u[3] = {C_devU.x, C_devU.y, C_devU.z};
                float C_v[3] = {C_devV.x, C_devV.y, C_devV.z};
                float normal3[3];
                cross(C_v, C_u, normal3);
                normalize(normal3);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal3[0]) || isnan(normal3[1]) || isnan(normal3[2])) {
                    normal3[0] = 0.0f;
                    normal3[1] = 1.0f;
                    normal3[2] = 0.0f;
                }

                float D_u[3] = {D_devU.x, D_devU.y, D_devU.z};
                float D_v[3] = {D_devV.x, D_devV.y, D_devV.z};
                float normal4[3];
                cross(D_v, D_u, normal4);
                normalize(normal4);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal4[0]) || isnan(normal4[1]) || isnan(normal4[2])) {
                    normal4[0] = 0.0f;
                    normal4[1] = 1.0f;
                    normal4[2] = 0.0f;
                }
                // Primeiro triângulo ABC
                buffers.addTriangle(A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
                buffers.addNormals(normal1[0], normal1[1], normal1[2], normal2[0], normal2[1], normal2[2], normal3[0], normal3[1], normal3[2]);
                buffers.addTextureCoordinates(u[i][j], v[i][j], u[i][j+1], v[i][j+1], u[i+1][j], v[i+1][j]);

                // Segundo triângulo CBD
                buffers.addTriangle(C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
                buffers.addNormals(normal3[0], normal3[1], normal3[2], normal2[0], normal2[1], normal2[2], normal4[0], normal4[1], normal4[2]);
                buffers.addTextureCoordinates(u[i+1][j], v[i+1][j], u[i][j+1], v[i][j+1], u[i+1][j+1], v[i+1][j+1]);

            }
        }

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

        float maxDist2_local = 0.0f;
        for (size_t i = 0; i < verts.size(); i += 3) {
            float dx = verts[i] - cx;
            float dy = verts[i + 1] - cy;
            float dz = verts[i + 2] - cz;
            float d2 = dx*dx + dy*dy + dz*dz;
            if (d2 > maxDist2_local) maxDist2_local = d2;
        }
        buffers.setRaioEsfera(sqrt(maxDist2_local));
    }

    return buffers;

}
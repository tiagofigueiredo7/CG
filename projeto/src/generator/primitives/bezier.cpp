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

        for (int i = 0; i < tesselation + 1; i++){
            for (int j = 0; j < tesselation + 1; j++){
                superficie[i][j] = bezier(u[i][j],v[i][j],&valores);
            }
        }

        // É usado tesselation sem o +1, visto que ele vai ler 4 pontos/1 quadrado/2 triangulos de uma vez
        for (int i = 0; i < tesselation; i++){
            for (int j = 0; j < tesselation; j++){
                Point3D A = superficie[i][j];
                Point3D B = superficie[i][j+1];
                Point3D C = superficie[i+1][j];
                Point3D D = superficie[i+1][j+1];

                // Primeiro triângulo ABC
                float AB[3] = {B.x - A.x, B.y - A.y, B.z - A.z};//Talvez seja melhor calcular as normais sem aproximações??
                float AC[3] = {C.x - A.x, C.y - A.y, C.z - A.z};
                float normal1[3];
                cross(AB, AC, normal1);
                normalize(normal1);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal1[0]) || isnan(normal1[1]) || isnan(normal1[2])) {
                    normal1[0] = 0.0f;
                    normal1[1] = 1.0f;
                    normal1[2] = 0.0f;
                }

                buffers.addTriangle(A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
                buffers.addNormals(normal1[0], normal1[1], normal1[2], normal1[0], normal1[1], normal1[2], normal1[0], normal1[1], normal1[2]);
                buffers.addTextureCoordinates(u[i][j], v[i][j], u[i][j+1], v[i][j+1], u[i+1][j], v[i+1][j]);

                // Segundo triângulo CBD
                float CB[3] = {B.x - C.x, B.y - C.y, B.z - C.z};
                float CD[3] = {D.x - C.x, D.y - C.y, D.z - C.z};
                float normal2[3];
                cross(CB, CD, normal2);
                normalize(normal2);

                // Se normalize deu NaN, usar normal default
                if (isnan(normal2[0]) || isnan(normal2[1]) || isnan(normal2[2])) {
                    normal2[0] = 0.0f;
                    normal2[1] = 1.0f;
                    normal2[2] = 0.0f;
                }

                buffers.addTriangle(C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
                buffers.addNormals(normal2[0], normal2[1], normal2[2], normal2[0], normal2[1], normal2[2], normal2[0], normal2[1], normal2[2]);
                buffers.addTextureCoordinates(u[i+1][j], v[i+1][j], u[i][j+1], v[i][j+1], u[i+1][j+1], v[i+1][j+1]);

            }
        }

    }

    return buffers;

}
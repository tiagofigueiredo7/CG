#include "generator/primitives/bezier.hpp"

struct _3DPoint {
    float x;
    float y;
    float z;
};

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

vector<float> generateBezierModel(char* file_path, int tesselation) {

    Patch data = Patch();
    data.parse_Patch_File(file_path);

    vector<float> vertices;

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

                addTriangle(vertices, A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
                addTriangle(vertices, C.x, C.y, C.z, B.x, B.y, B.z, D.x, D.y, D.z);
            }
        }

    }

    return vertices;

}
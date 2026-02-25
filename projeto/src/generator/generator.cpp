#include "generator/generator.hpp"

// Armazena os vértices gerados no ficheiro
void storeVertices(const vector<float>& vertices, const string& file) {
    ofstream out("../models/" + file);
    if (!out.is_open()) {
        cerr << "[ERRO] Não foi possível abrir o ficheiro.";
        return;
    }
    for (size_t i = 0; i < vertices.size(); i += 3) {
        out << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n"; // um ponto (3 coordenadas) por linha
    }
    out.close();
}

int main(int argc, char** argv) {

    // Variaveis para a verificação do input do generator
    const int parameters = argc;
    const string figure = argv[1];
    const string file = argv[argc - 1];

    if(checkInput(parameters, figure) == false) {
        return 1;
    }

	vector <float> vertices;

    if (figure == "plane") {
        vertices = generatePlane(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "box") {
        vertices = generateBox(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "sphere") {
        vertices = generateSphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4])); 
    }
    else if (figure == "cone") {
        vertices = generateCone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
    }
    else if (figure == "torus") {
        vertices = generateTorus(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
    }
    else if(figure == "cilinder") {
        vertices = generateCilinder(stof(argv[2]), stof(argv[3]), stoi(argv[4]));
    }
    else {
        cerr << "[ERRO] Figura não suportada.";
        return 1;
    }

    storeVertices(vertices, file);

    return 0;
}
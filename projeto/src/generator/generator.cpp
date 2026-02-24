#include "generator/generator.hpp"

// Armazena os vértices gerados no ficheiro
void storeVertices(const vector<float>& vertices, const string& file) {
    ofstream out("./models/" + file);
    if (!out.is_open()) {
        cerr << "ERRO: Não foi possível abrir o ficheiro.";
        return;
    }
    for (size_t i = 0; i < vertices.size(); i += 3) {
        out << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n"; // um ponto (3 coordenadas) por linha
    }
    out.close();
}

int main(int argc, char** argv) {
    if (argc < 5) {
        cerr << "ERRO: Parâmetros insuficientes.";
        return 1; 
    }

	vector <float> vertices;
    const string file = argv[argc - 1];
    const string figure = argv[1];

    if (figure == "plane" && argc == 5) {
        vertices = generatePlane(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "box" && argc == 5) {
        vertices = generateBox(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "sphere" && argc == 6) {
        vertices = generateSphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4])); 
    }
    else if (figure == "cone" && argc == 7) {
        vertices = generateCone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
    }
    else {
        cerr << "ERRO: Parâmetros inválidos.\nUSAGE: generator <primitive> <params> <dest file>";
        return 1;
    }

    storeVertices(vertices, file);

    return 0;
}
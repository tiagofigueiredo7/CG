#include "generator/main.hpp"

// Armazena os vértices gerados no ficheiro
void storeVertices(const std::vector<float>& vertices, const std::string& file) {
    std::ofstream out(file);
    if (!out.is_open()) {
        std::cerr << "ERRO: Não foi possível abrir o ficheiro.";
        return;
    }
    for (size_t i = 0; i < vertices.size(); i += 3) {
        out << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n"; // um ponto (3 coordenadas) por linha
    }
    out.close();
}

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "ERRO: Parâmetros insuficientes.";
        return 1; 
    }

	std::vector <float> vertices;
    const std::string file = argv[argc - 1];
    const std::string figure = argv[1];

    if (figure == "plane" && argc == 5) {
        vertices = generatePlane(std::stof(argv[2]), std::stoi(argv[3]));
    }
    else if (figure == "box" && argc == 5) {
        vertices = generateBox(std::stof(argv[2]), std::stoi(argv[3]));
    }
    else if (figure == "sphere" && argc == 6) {
        //vertices = generateSphere(std::stof(argv[2]), std::stoi(argv[3]), std::stoi(argv[4])); 
    }
    else if (figure == "cone" && argc == 7) {
        //vertices = generateCone(std::stof(argv[2]), std::stof(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
    }
    else {
        std::cerr << "ERRO: Parâmetros inválidos.\nUSAGE: generator <primitive> <params> <dest file>";
        return 1;
    }

    storeVertices(vertices, file);

    return 0;
}
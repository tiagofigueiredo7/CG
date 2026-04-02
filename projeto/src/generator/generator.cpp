#include "generator/generator.hpp"

int main(int argc, char** argv) {

    // Variaveis para a verificação do input do generator
    const int parameters = argc;
    const string figure = argv[1];
    const string file = argv[argc - 1];

    if(checkInputGenerator(parameters, figure) == false) {
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
    else if (figure == "cylinder") {
        vertices = generateCylinder(stof(argv[2]), stof(argv[3]), stoi(argv[4]));
    }
    else if (figure == "patch") {
        vertices = generateBezierModel(argv[2], stoi(argv[3]));
    }
    else if (figure == "fita_mobius") {
        vertices = generateFitaMobius(stof(argv[2]), stof(argv[3]), stoi(argv[4]));
    }
    else {
        cerr << "[ERRO] Figura não suportada.\n";
        return 1;
    }

    storeVertices(vertices, file);

    return 0;
}
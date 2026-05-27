#include "generator/generator.hpp"

int main(int argc, char** argv) {

    // Variaveis para a verificação do input do generator
    const int parameters = argc;
    const string figure = argv[1];
    const string file = argv[argc - 1];

    if(checkInputGenerator(parameters, figure) == false) {
        return 1;
    }

    PrimitiveBuffers buffers;

    if (figure == "plane") {
        buffers = generatePlane(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "box") {
        buffers = generateBox(stof(argv[2]), stoi(argv[3]));
    }
    else if (figure == "sphere") {
        buffers = generateSphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4])); 
    }
    else if (figure == "cone") {
        buffers = generateCone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
    }
    else if (figure == "torus") {
        buffers = generateTorus(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
    }
    else if (figure == "cylinder") {
        buffers = generateCylinder(stof(argv[2]), stof(argv[3]), stoi(argv[4]));
    }
    else if (figure == "patch") {
        buffers = generateBezierModel(argv[2], stoi(argv[3]));
    }
    else if (figure == "mobiusStrip") {
        buffers = generateMobiusStrip(stof(argv[2]), stof(argv[3]), stoi(argv[4]));
    }
    else if (figure == "kleinBottle") {
        buffers = generateKleinBottle(stoi(argv[2]), stoi(argv[3]), stof(argv[4]), stof(argv[5]), stof(argv[6]));
    }
    else {
        cerr << "[ERRO] Figura não suportada.\n";
        return 1;
    }

    buffers.storeBuffers(file);

    return 0;
}
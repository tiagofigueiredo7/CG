// Generator
// não deve estar a funcionar, ainda não testei por causa de uns problemas no windows
// faltam includes


// armazena os vértices gerados no ficheiro
void storeVertices(const vector<float>& vertices, const string& file) {
    ofstream out(file);
    if (!out.is_open()) {
        cerr << "ERRO: Não foi possível abrir o ficheiro.";
        return;
    }
    for (size_t i = 0; i < vertices.size(); i += 3) {
        out << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n";
    }
    out.close();
}

int main(int argc, char** argv) {
    if (argc < 5) {
        cerr << "ERRO: Parâmetros insuficientes.";
        return 1; 
    }

	vector <float> vertices;
    string file = argv[argc - 1];

    switch (argv[1]) {
        case "plane":
            if (argc == 5) {
                vertices = generatePlane(stof(argv[2]), stoi(argv[3]));
                break;
            }
            else {
                cerr << "ERRO: Parâmetros incorretos.\nExemplo: generator plane <length> <#divisions> <dest file>";
                return 1;
			}
        case "box":
            if (argc == 5) { 
				vertices = generateBox(stof(argv[2]), stoi(argv[3]));
                break;
            }
            else {
                cerr << "ERRO: Parâmetros incorretos.\nExemplo: generator box <length> <#divisions> <dest file>";
                return 1;
            }
        case "sphere":
            if (argc == 6) {
                // ainda por fazer
				vertices = generateSphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4]));
                break;
            }
            else {
                cerr << "ERRO: Parâmetros incorretos.\nExemplo: generator sphere <radius> <#slices> <#stacks> <dest file>";
                return 1;
            }
        case "cone":
            if (argc == 7) {
                // ainda por fazer
				vertices = generateCone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]));
                break;
            }
            else {
                cerr << "ERRO: Parâmetros incorretos.\nExemplo: generator cone <radius> <height> <#slices> <#stacks> <dest file>";
                return 1;
            }
        default:
            cerr << "ERRO: Primitiva desconhecida.";
            return 1;
    }

    storeVertices(vertices, file);

    return 0;
}
#include "generator/Patch.hpp"

Patch::Patch() {
    this->patches_count = 0;
    this->control_points_count = 0;
    this->indices_patch = nullptr;
    this->control_points_values = vector<float>();
}

Patch::~Patch() {
    for (int i = 0; i < this->patches_count; i++) {
        free(this->indices_patch[i]);
    }
    free(this->indices_patch);
}

int Patch::getPatchesCount() {
    return this->patches_count;
}

vector<float>* Patch::getIndicesPatch(int index) {
    return this->indices_patch[index];
}

int Patch::getControlPointsCount() {
    return this->control_points_count;
}

vector<float> Patch::getControlPointsValues() {
    return this->control_points_values;
}

void Patch::parse_Patch_File(char* file_path) {

    // Abrir o ficheiro
    ifstream file(file_path);
    if (!file.is_open()){
        cerr << "[ERRO] Erro ao abrir ficheiro: " << file_path << endl;
    }

    string line;

    // Ler o número de patches
    getline(file,line);

    int n_patches;
    istringstream iss_patches(line);
    if (!(iss_patches >> n_patches)) {
            cerr << "[ERRO] Erro ao ler número de patches: " << line << endl;
            return;
    }

    this->setPatchesCount(n_patches);

    // Ler os índices dos patches
    this->indices_patch = (vector<float>**) malloc(n_patches * sizeof(vector<float>*));


    for(int i = 0; i<n_patches;i++){//ACABAR
        this->indices_patch[i] = new vector<float>();
        getline(file,line);


        for (char c : line) {
            if (c == ' ' || c == '\t') {
                continue; // Ignorar espaços em branco
            }
            if (c == ',') {
                continue; // Ignorar vírgulas
            }

            /*                    
            
            
            
            
            
            */


        }
        
    }

    // Ler o número de control points
    getline(file,line);

    int n_control_points;
    istringstream iss_n_control_points(line);
    if (!(iss_n_control_points >> n_control_points)) {
            cerr << "[ERRO] Erro ao ler número de control points: " << line << endl;
            return;
    }
    this->setControlPointsCount(n_control_points);

    // Ler os valores dos control points
    for (int i = 0; i < n_control_points; i++) {
        float x, y, z;
        istringstream iss_xyz(line);
        if (!(iss_xyz >> x >> y >> z)) {
                cerr << "[ERRO] Erro ao ler valores dos control points: " << line << endl;
                return;
        }

        this->control_points_values.push_back(x);
        this->control_points_values.push_back(y);
        this->control_points_values.push_back(z);
    }

    file.close();
}

void Patch::setPatchesCount(int count) {
    this->patches_count = count;
}

void Patch::setControlPointsCount(int count) {
    this->control_points_count = count;
}

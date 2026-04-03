#include "generator/BezierPatch.hpp"

BezierPatch::BezierPatch() {
    this->patches_count = 0;
    this->control_points_count = 0;
    this->indices_patch = nullptr;
    this->control_points_values = vector<float>();
}

BezierPatch::~BezierPatch() {
    for (int i = 0; i < this->patches_count; i++) {
        free(this->indices_patch[i]);
    }
    free(this->indices_patch);
}

int BezierPatch::getPatchesCount() {
    return this->patches_count;
}

vector<float>* BezierPatch::getIndicesPatch(int index) {
    return this->indices_patch[index];
}

int BezierPatch::getControlPointsCount() {
    return this->control_points_count;
}

vector<float> BezierPatch::getControlPointsValues() {
    return this->control_points_values;
}

void BezierPatch::parse_Patch_File(char* file_path) {

    // Abrir o ficheiro
    ifstream file(file_path);
    if (!file.is_open()){
        cerr << "[ERRO] Erro ao abrir ficheiro: " << file_path << endl;
        return;
    }

    string line;

    // Ler o número de patches
    getline(file,line);

    int n_patches;
    istringstream iss_patches(line);
    if (!(iss_patches >> n_patches)) {
        cerr << "[ERRO] Erro ao ler número de patches: " << line << endl;
        file.close();
        return;
    }

    this->setPatchesCount(n_patches);

    // Ler os índices dos patches
    this->indices_patch = (vector<float>**) malloc(n_patches * sizeof(vector<float>*));

    for(int i = 0; i < n_patches; i++){
        this->indices_patch[i] = new vector<float>();
        getline(file, line);

        istringstream iss(line);
        string index_str;
        while (getline(iss, index_str, ',')) {
            int index;
            istringstream index_stream(index_str);
            if (index_stream >> index) {
                this->indices_patch[i]->push_back(index);
            }

        }
        
    }

    // Ler o número de control points
    getline(file,line);

    int n_control_points;
    istringstream iss_n_control_points(line);
    if (!(iss_n_control_points >> n_control_points)) {
        cerr << "[ERRO] Erro ao ler número de control points: " << line << endl;
        file.close();
        return;
    }
    this->setControlPointsCount(n_control_points);

    // Ler os valores dos control points
    for (int i = 0; i < n_control_points; i++) {
        getline(file, line);
        
        // Parse comma-separated coordinates
        istringstream iss(line);
        string str;
        vector<float> control_point;
        
        while (getline(iss, str, ',')) {
            float coord;
            istringstream coord_stream(str);
            if (coord_stream >> coord) {
                control_point.push_back(coord);
            }
        }
        
        if (control_point.size() == 3) {
            this->control_points_values.push_back(control_point[0]);
            this->control_points_values.push_back(control_point[1]);
            this->control_points_values.push_back(control_point[2]);
        } else {
            cerr << "[ERRO] Erro ao ler valores dos control points: " << line << endl;
            file.close();
            return;
        }
    }

    file.close();
}

void BezierPatch::setPatchesCount(int count) {
    this->patches_count = count;
}

void BezierPatch::setControlPointsCount(int count) {
    this->control_points_count = count;
}

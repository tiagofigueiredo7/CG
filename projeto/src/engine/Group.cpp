#include "engine/Group.hpp"

// Construtor
Group::Group() {}

// Destrutor
Group::~Group() {
    for (Transformation* t : this->getTransformations()){
        delete t;
    }

    for (char* c: this->getModelFiles()){
        free(c);
    }

    for (Group* g: this->getSubGroups()){
        delete g;
    }

}

// Getters
vector<Transformation*> Group::getTransformations() { return transformations; }

vector<char *> Group::getModelFiles() { return model_files; }

vector<Group* >Group::getSubGroups(){ return subgroups; }

// Add
void Group::addTransformation(Transformation* transf){ transformations.push_back(transf); }

void Group::addModelFile(char* model_file) { model_files.push_back(model_file); }

void Group::addSubGroup(Group* subgroup) { subgroups.push_back(subgroup); }

// Print
void Group::print(int depth) {
 /*   
    string indent(depth * 2, ' ');
    
    cout << indent << "[GRUPO Nível " << depth << "]" << "\n";
    
    if (!transformations.empty()) {
        cout << indent << "  Transformações:" << "\n";
        for (const auto& t : transformations) {
            cout << indent << "    - ";
            if (t.type == 0) cout << "Translação";
            else if (t.type == 1) cout << "Rotação";
            else if (t.type == 2) cout << "Escala";
            cout << ": x=" << t.x << ", y=" << t.y << ", z=" << t.z;
            if (t.type == 1) cout << ", ângulo=" << t.angle;
            cout << "\n";
        }
    }
    
    if (!model_files.empty()) {
        cout << indent << "  Ficheiros de Modelo:" << "\n";
        for (const auto& file : model_files) {
            cout << indent << "    - " << file << "\n";
        }
    }
    
    if (!subgroups.empty()) {
        cout << indent << "  Subgrupos (" << subgroups.size() << "):" << "\n";
        for (size_t i = 0; i < subgroups.size(); i++) {
            cout << indent << "  └─ Subgrupo #" << (i + 1) << ":" << "\n";
            subgroups[i]->print(depth + 1);
        }
    }
    
    if (depth == 0) {
        cout << "\n";
    }
       */ 
}
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
#include "engine/Group.hpp"

// Construtor
Group::Group() {
    this->buffer = (GLuint*)malloc(sizeof(GLuint));
    this->buffer[0] = 0;
    this->transformations = vector<Transformation*>();
    this->subgroups = vector<Group*>();
    this->vertices_count = vector<int>();
}

// Destrutor
Group::~Group() {
    for (Transformation* t : this->getTransformations()){
        delete t;
    }

    for (Group* g: this->getSubGroups()){
        delete g;
    }

    // Liberar VBO da GPU antes de liberar o ponteiro
    if (this->buffer[0] != 0) {
        glDeleteBuffers(1, this->buffer);
    }

    free(this->buffer);

}

// Getters
vector<Transformation*> Group::getTransformations() { return transformations; }

vector<Group* >Group::getSubGroups(){ return subgroups; }

GLuint* Group::getBuffer(){ return buffer; }

vector<int> Group::getVerticesCount() { return vertices_count; }

// Add
void Group::addTransformation(Transformation* transf){ transformations.push_back(transf); }

void Group::addSubGroup(Group* subgroup) { subgroups.push_back(subgroup); }

void Group::addVerticeCount(int count) { vertices_count.push_back(count); }

// Print
void Group::print(int depth) {
    // Refazer
}

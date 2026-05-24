#include "generator/PrimitiveBuffers.hpp"

PrimitiveBuffers::PrimitiveBuffers() {
    this->vertices = vector<float>();
    this->normais = vector<float>();
    this->textures = vector<float>();

    this->raio_esfera = 0.0f;
    this->center_x = 0.0f;
    this->center_y = 0.0f;
    this->center_z = 0.0f;
}

vector<float> PrimitiveBuffers::getVertices() { return vertices; }
vector<float> PrimitiveBuffers::getNormais() { return normais; }
vector<float> PrimitiveBuffers::getTextures() { return textures; }
float PrimitiveBuffers::getRaioEsfera() { return raio_esfera; }
float PrimitiveBuffers::getCenterX() { return center_x; }
float PrimitiveBuffers::getCenterY() { return center_y; }
float PrimitiveBuffers::getCenterZ() { return center_z; }

void PrimitiveBuffers::setRaioEsfera(float raio) { this->raio_esfera = raio; }
void PrimitiveBuffers::setCenter(float x, float y, float z) {
    this->center_x = x;
    this->center_y = y;
    this->center_z = z;
}

// Adiciona coordenadas dos vértices de um trinânculo a um vetor
void PrimitiveBuffers::addTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    vertices.push_back(x1);
    vertices.push_back(y1);
    vertices.push_back(z1);
    vertices.push_back(x2);
    vertices.push_back(y2);
    vertices.push_back(z2);
    vertices.push_back(x3);
    vertices.push_back(y3);
    vertices.push_back(z3);
}

void PrimitiveBuffers::addNormals(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    normais.push_back(x1);
    normais.push_back(y1);
    normais.push_back(z1);
    normais.push_back(x2);
    normais.push_back(y2);
    normais.push_back(z2);
    normais.push_back(x3);
    normais.push_back(y3);
    normais.push_back(z3);
}

void PrimitiveBuffers::addTextureCoordinates(float u1, float v1, float u2, float v2, float u3, float v3) {
    textures.push_back(u1);
    textures.push_back(v1);
    textures.push_back(u2);
    textures.push_back(v2);
    textures.push_back(u3);
    textures.push_back(v3);
}

void PrimitiveBuffers::storeBuffers(string file) {
    vector<float> vertices = this->getVertices();
    vector<float> normais = this->getNormais();
    vector<float> textures = this->getTextures();

    ofstream out("../models/" + file);
    if (!out.is_open()) {
        cerr << "[ERRO] Não foi possível abrir o ficheiro.";
        return;
    }
    out << "radius " << raio_esfera << "\n";
    out << "centerX " << center_x << ", centerY " << center_y << ", centerZ " << center_z << "\n";
    out << "count " << vertices.size() / 3 << "\n"; // número de vértices (3 coordenadas por vértice)
    for (size_t i = 0; i < vertices.size(); i += 3) {
        out << "v " << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n"; // um ponto (3 coordenadas) por linha
    }
    for (size_t i = 0; i < normais.size(); i += 3) {
        out << "n " << normais[i] << " " << normais[i + 1] << " " << normais[i + 2] << "\n"; // uma normal (3 coordenadas) por linha
    }
    for (size_t i = 0; i < textures.size(); i += 2) {
        out << "t " << textures[i] << " " << textures[i + 1] << "\n"; // uma coordenada de textura (2 coordenadas) por linha
    }
    out.close();
}
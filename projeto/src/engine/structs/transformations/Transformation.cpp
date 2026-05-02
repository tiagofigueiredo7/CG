#include "engine/structs/transformations/Transformation.hpp"

// Construtores
Transformation::Transformation() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Transformation::Transformation(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// Destrutor virtual
Transformation::~Transformation() {}

// Getters
float Transformation::getX() { return x; }
float Transformation::getY() { return y; }
float Transformation::getZ() { return z; }

// Setters
void Transformation::setX(float novoX) { x = novoX; }
void Transformation::setY(float novoY) { y = novoY; }
void Transformation::setZ(float novoZ) { z = novoZ; }
#include "engine/transformations/Rotate.hpp"

// Construtores
Rotate::Rotate(float x, float y, float z, float angle) : Transformation(x, y, z) {
    this->angle = angle;
}

Rotate::Rotate() : Transformation() {
    this->angle = 0;
}

// Getter
float Rotate::getAngle() { return this->angle; }

// Setter
void Rotate::setAngle(float novoAngle) { this->angle = novoAngle; }
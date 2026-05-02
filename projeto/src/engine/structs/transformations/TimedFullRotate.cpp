#include "engine/structs/transformations/TimedFullRotate.hpp"

// Construtores
TimedFullRotate::TimedFullRotate(float x, float y, float z, float time) : Transformation(x, y, z) {
    this->time = time;
}

TimedFullRotate::TimedFullRotate() : Transformation() {
    this->time = 0;
}

// Getter
float TimedFullRotate::getTime() { return this->time; }

// Setter
void TimedFullRotate::setTime(float novoTime) { this->time = novoTime; }
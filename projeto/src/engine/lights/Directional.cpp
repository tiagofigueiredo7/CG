#include "engine/lights/Directional.hpp"

Directional::Directional(float x, float y, float z) : Light() {
    this->dirX = x;
    this->dirY = y;
    this->dirZ = z;
}

float Directional::getDirX() { return dirX; }
float Directional::getDirY() { return dirY; }
float Directional::getDirZ() { return dirZ; }

void Directional::setDirX(float x) { dirX = x; }
void Directional::setDirY(float y) { dirY = y; }
void Directional::setDirZ(float z) { dirZ = z; }
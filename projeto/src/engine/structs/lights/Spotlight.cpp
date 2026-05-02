#include "engine/structs/lights/Spotlight.hpp"

Spotlight::Spotlight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff) : Light() {
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;

    this->dirX = dirX;
    this->dirY = dirY;
    this->dirZ = dirZ;

    this->cutoff = cutoff;
}

float Spotlight::getDirX() { return dirX; }
float Spotlight::getDirY() { return dirY; }
float Spotlight::getDirZ() { return dirZ; }

void Spotlight::setDirX(float x) { dirX = x; }
void Spotlight::setDirY(float y) { dirY = y; }
void Spotlight::setDirZ(float z) { dirZ = z; }

float Spotlight::getPosX() { return posX; }
float Spotlight::getPosY() { return posY; }
float Spotlight::getPosZ() { return posZ; }

void Spotlight::setPosX(float x) { posX = x; }
void Spotlight::setPosY(float y) { posY = y; }
void Spotlight::setPosZ(float z) { posZ = z; }

float Spotlight::getCutoff() { return cutoff; }
void Spotlight::setCutoff(float cutoff) { cutoff = cutoff; }
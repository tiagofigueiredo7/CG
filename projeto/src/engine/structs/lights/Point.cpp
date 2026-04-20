#include "engine/structs/lights/Point.hpp"

Point::Point(float x, float y, float z) : Light() {
    this->posX = x;
    this->posY = y;
    this->posZ = z;
}

float Point::getPosX() { return posX; }
float Point::getPosY() { return posY; }
float Point::getPosZ() { return posZ; }

void Point::setPosX(float x) { posX = x; }
void Point::setPosY(float y) { posY = y; }
void Point::setPosZ(float z) { posZ = z; }
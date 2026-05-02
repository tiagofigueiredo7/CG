#include "engine/structs/camera/Camera.hpp"

Camera::Camera() {
    // Vlores Padrão
    posX = 0.0f;
    posY = 0.0f;
    posZ = 5.0f;

    lookX = 0.0f;
    lookY = 0.0f;
    lookZ = -1.0f;

    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
}

Camera::Camera(Camera* cam) {
    posX = cam->getPosX();
    posY = cam->getPosY();
    posZ = cam->getPosZ();

    lookX = cam->getLookX();
    lookY = cam->getLookY();
    lookZ = cam->getLookZ();

    upX = cam->getUpX();
    upY = cam->getUpY();
    upZ = cam->getUpZ();
}

Camera::~Camera() {}


// Getters

float Camera::getPosX() { return posX; }

float Camera::getPosY() { return posY; }

float Camera::getPosZ() { return posZ; }

float Camera::getLookX() { return lookX; }

float Camera::getLookY() { return lookY; }

float Camera::getLookZ() { return lookZ; }

float Camera::getUpX() { return upX; }

float Camera::getUpY() { return upY; }

float Camera::getUpZ() { return upZ; }

//Setters

void Camera::setPosX(float x) { posX = x; }

void Camera::setPosY(float y) { posY = y; }

void Camera::setPosZ(float z) { posZ = z; }

void Camera::setLookX(float x) { lookX = x; }

void Camera::setLookY(float y) { lookY = y; }

void Camera::setLookZ(float z) { lookZ = z; }

void Camera::setUpX(float x) { upX = x; }

void Camera::setUpY(float y) { upY = y; }

void Camera::setUpZ(float z) { upZ = z; }
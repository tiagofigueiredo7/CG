#include "engine/structs/camera/ThirdPersonCamera.hpp"

ThirdPersonCamera::ThirdPersonCamera(int playersCount) : Camera() {
    targetIndex = -1;
    target = nullptr;

    numPlayers = playersCount;
    distance = 6.0f;
    height = 2.5f;
    lookHeight = 1.0f;

}

ThirdPersonCamera::ThirdPersonCamera(Camera* cam, int playersCount) : Camera(*cam) {

    targetIndex = -1;
    target = nullptr;

    numPlayers = playersCount;
    distance = 6.0f;
    height = 2.5f;
    lookHeight = 1.0f;

    update_camera_Pos();
    update_camera_LookAt();
}

void ThirdPersonCamera::update_camera_Pos() {
    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;

    if (target != nullptr) {
        Point3D p = target->getGlobalPosition();
        targetX = p.x;
        targetY = p.y;
        targetZ = p.z;
    }

    this->setPosX(targetX);
    this->setPosY(targetY + height);
    this->setPosZ(targetZ + distance);
}

void ThirdPersonCamera::update_camera_LookAt() {
    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;

    if (target != nullptr) {
        Point3D p = target->getGlobalPosition();
        targetX = p.x;
        targetY = p.y;
        targetZ = p.z;
    }

    this->setLookX(targetX);
    this->setLookY(targetY + lookHeight);
    this->setLookZ(targetZ);
}

int ThirdPersonCamera::getTargetIndex() {
    return targetIndex;
}

void ThirdPersonCamera::incrementTargetIndex() {
    if (numPlayers == 0) return;
    else if (targetIndex == -1) {
        targetIndex = 0;
    } else {
        targetIndex = (targetIndex + 1) % numPlayers;
    }
}

void ThirdPersonCamera::setTarget(Group* target) {
    this->target = target;
    update_camera_Pos();
    update_camera_LookAt();
}

Group* ThirdPersonCamera::getTarget() {
    return target;
}

float ThirdPersonCamera::getDistance() {
    return distance;
}

float ThirdPersonCamera::getHeight() {
    return height;
}

float ThirdPersonCamera::getLookHeight() {
    return lookHeight;
}

void ThirdPersonCamera::setDistance(float value) {
    distance = value;
}

void ThirdPersonCamera::setHeight(float value) {
    height = value;
}

void ThirdPersonCamera::setLookHeight(float value) {
    lookHeight = value;
}
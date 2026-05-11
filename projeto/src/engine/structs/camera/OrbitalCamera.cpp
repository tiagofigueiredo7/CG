#include "engine/structs/camera/OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera(int playersCount) : Camera() {
    calculate_spherical_from_camera(this);
    zoom_speed = 0.1f;
    this->setLookX(0.0f);
    this->setLookY(0.0f);
    this->setLookZ(0.0f);

    targetIndex = -1;
    target = nullptr;

    numPlayers = playersCount;

}

OrbitalCamera::OrbitalCamera(Camera* cam, int playersCount) : Camera(*cam) {
    calculate_spherical_from_camera(cam);
    zoom_speed = 0.1f;
    this->setLookX(0.0f);
    this->setLookY(0.0f);
    this->setLookZ(0.0f);

    targetIndex = -1;
    target = nullptr;

    numPlayers = playersCount;
}

void OrbitalCamera::calculate_spherical_from_camera(Camera* cam) {
    float Posx = cam->getPosX();
    float Posy = cam->getPosY();
    float Posz = cam->getPosZ();

    float radius = sqrt(Posx * Posx + Posy * Posy + Posz * Posz);
    if (radius < 1e-6f) {
        alpha_coord = 0.0f;
        beta_coord = 0.0f;
        radius_coord = 5.0f;
        return;
    }

    alpha_coord = atan2(Posx, Posz);

    float sinBeta = Posy / radius;
    if (sinBeta > 1.0f) sinBeta = 1.0f;
    if (sinBeta < -1.0f) sinBeta = -1.0f;
    beta_coord = asin(sinBeta);

    radius_coord = radius;
}

void OrbitalCamera::update_cartesian_coordinates(){

    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;

    if (target != nullptr) {
        Pos p = target->getGlobalPosition();
        targetX = p.x;
        targetY = p.y;
        targetZ = p.z;
    }

    this->setPosX(targetX + radius_coord * cos(beta_coord) * sin(alpha_coord));
    this->setPosY(targetY + radius_coord * sin(beta_coord));
    this->setPosZ(targetZ + radius_coord * cos(beta_coord) * cos(alpha_coord));

    this->setLookX(targetX);
    this->setLookY(targetY);
    this->setLookZ(targetZ);
}

void OrbitalCamera::update_alpha(float a){
    alpha_coord += a;
}

void OrbitalCamera::update_beta(float b){
    beta_coord += b;
}

void OrbitalCamera::update_radius(float r){
    radius_coord += r;
}

void OrbitalCamera::update_zoom_speed(float z){
    zoom_speed += z;
}

void OrbitalCamera::set_alpha(float a){
    alpha_coord = a;
}

void OrbitalCamera::set_beta(float b){
    beta_coord = b;
}

void OrbitalCamera::set_radius(float r){
    radius_coord = r;
}

void OrbitalCamera::set_zoom_speed(float z){
    zoom_speed = z;
}

float OrbitalCamera::get_alpha(){
    return alpha_coord;
}

float OrbitalCamera::get_beta(){
    return beta_coord;
}

float OrbitalCamera::get_radius(){
    return radius_coord;
}

float OrbitalCamera::get_zoom_speed(){
    return zoom_speed;
}

int OrbitalCamera::getTargetIndex() {
    return targetIndex;
}

void OrbitalCamera::incrementTargetIndex() {
    if (numPlayers == 0) return;
    else if (targetIndex == -1) {
        targetIndex = 0;
    } else {
        targetIndex = (targetIndex + 1) % numPlayers;
    }
}

void OrbitalCamera::setTarget(Group* target) {
    this->target = target;
    update_cartesian_coordinates();
}

Group* OrbitalCamera::getTarget() {
    return target;
}
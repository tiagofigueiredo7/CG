#include "engine/camera/OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera() : Camera() {
    calculate_spherical_from_camera(this);
    zoom_speed = 0.1f;
    this->setLookX(0.0f);
    this->setLookY(0.0f);
    this->setLookZ(0.0f);

}

OrbitalCamera::OrbitalCamera(Camera* cam) : Camera(*cam) {
    calculate_spherical_from_camera(cam);
    zoom_speed = 0.1f;
    this->setLookX(0.0f);
    this->setLookY(0.0f);
    this->setLookZ(0.0f);
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
    this->setPosX(radius_coord * cos(beta_coord) * sin(alpha_coord));
    this->setPosY(radius_coord * sin(beta_coord));
    this->setPosZ(radius_coord * cos(beta_coord) * cos(alpha_coord));
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
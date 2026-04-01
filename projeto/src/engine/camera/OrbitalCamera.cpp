#include "engine/camera/OrbitalCamera.hpp"

OrbitalCamera::OrbitalCamera() : Camera() {
    alpha_coord = 0.0f;
    beta_coord = 0.0f;
    radius_coord = 5.0f;
}

OrbitalCamera::OrbitalCamera(Camera* cam) : Camera(*cam) {
    alpha_coord = 0.0f;
    beta_coord = 0.0f;
    radius_coord = 5.0f;
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

void OrbitalCamera::set_alpha(float a){
    alpha_coord = a;
}

void OrbitalCamera::set_beta(float b){
    beta_coord = b;
}

void OrbitalCamera::set_radius(float r){
    radius_coord = r;
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
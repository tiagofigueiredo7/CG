#include "engine/camera/FirstPersonCamera.hpp"

FirstPersonCamera::FirstPersonCamera() : Camera() {
    alpha = 0.0f;
    move_speed = 0.5f;

    startX = 0.0f;
    startY = 0.0f;

    tracking = 0.0f;

    keyW = false;
    keyA = false;
    keyS = false;
    keyD = false;

}

FirstPersonCamera::FirstPersonCamera(Camera* cam) : Camera(Camera(*cam)) {
    alpha = 0.0f;
    move_speed = 0.5f;

    startX = 0.0f;
    startY = 0.0f;

    tracking = 0.0f;

    keyW = false;
    keyA = false;
    keyS = false;
    keyD = false;

}

void FirstPersonCamera::update_camera() {
    // Acabar
}

void FirstPersonCamera::set_alpha(float a) { alpha = a; }
void FirstPersonCamera::set_move_speed(float s) { move_speed = s; }
void FirstPersonCamera::set_keyW(bool state) { keyW = state; }
void FirstPersonCamera::set_keyA(bool state) { keyA = state; }
void FirstPersonCamera::set_keyS(bool state) { keyS = state; }
void FirstPersonCamera::set_keyD(bool state) { keyD = state; }
void FirstPersonCamera::set_tracking(float t) { tracking = t; }
void FirstPersonCamera::set_startX(float x) { startX = x; }
void FirstPersonCamera::set_startY(float y) { startY = y; }

float FirstPersonCamera::get_alpha() { return alpha; }
float FirstPersonCamera::get_move_speed() { return move_speed; }
bool FirstPersonCamera::get_keyW() { return keyW; }
bool FirstPersonCamera::get_keyA() { return keyA; }
bool FirstPersonCamera::get_keyS() { return keyS; }
bool FirstPersonCamera::get_keyD() { return keyD; }
float FirstPersonCamera::get_tracking() { return tracking; }
float FirstPersonCamera::get_startX() { return startX; }
float FirstPersonCamera::get_startY() { return startY; }


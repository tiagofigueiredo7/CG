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

void FirstPersonCamera::update_camera_LookAt() {
    // Convert alpha from degrees to radians
	float alpha_rad = alpha * M_PI / 180.0f;

    // Camera look-at point (horizontal, looking direction)
    this->setLookX(this->getPosX() + sin(alpha_rad));
    this->setLookY(this->getPosY());
    this->setLookZ(this->getPosZ() + cos(alpha_rad));
}

void FirstPersonCamera::update_camera_Pos() {
	
	// Convert alpha from degrees to radians
	float alpha_rad = alpha * M_PI / 180.0f;
	
	// Calculate direction vector: d = (sin(alpha), 0, cos(alpha))
	float dirX = sin(alpha_rad);
	float dirZ = cos(alpha_rad);
	
	// Calculate right vector: r = d × up = (cos(alpha), 0, -sin(alpha))
	float rightX = cos(alpha_rad);
	float rightZ = -sin(alpha_rad);
	
	// Forward/Backward motion (W/S keys)
	if (keyW) {
        this->setPosX(this->getPosX() + dirX * move_speed);
        this->setPosZ(this->getPosZ() + dirZ * move_speed);
	}
	if (keyS) {
		this->setPosX(this->getPosX() - dirX * move_speed);
		this->setPosZ(this->getPosZ() - dirZ * move_speed);
	}
	
	// Lateral motion (A/D keys)
	if (keyA) {
        this->setPosX(this->getPosX() + rightX * move_speed);
        this->setPosZ(this->getPosZ() + rightZ * move_speed);
	}
	if (keyD) {
		this->setPosX(this->getPosX() - rightX * move_speed);
        this->setPosZ(this->getPosZ() - rightZ * move_speed);
	}
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


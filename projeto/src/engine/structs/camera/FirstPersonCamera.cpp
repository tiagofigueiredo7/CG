#include "engine/structs/camera/FirstPersonCamera.hpp"

FirstPersonCamera::FirstPersonCamera() : Camera() {
    alpha = get_alpha_from_camera(this);
    beta = get_beta_from_camera(this);
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
    alpha = get_alpha_from_camera(cam);
    beta = get_beta_from_camera(cam);
    move_speed = 0.5f;

    startX = 0.0f;
    startY = 0.0f;

    tracking = 0.0f;

    keyW = false;
    keyA = false;
    keyS = false;
    keyD = false;

}

float FirstPersonCamera::get_alpha_from_camera(Camera* cam) {
    float dirX = cam->getLookX() - cam->getPosX();
    float dirZ = cam->getLookZ() - cam->getPosZ();

    if (fabs(dirX) < 1e-6f && fabs(dirZ) < 1e-6f) {
        return 0.0f;
    }

    return atan2(dirX, dirZ) * 180.0f / M_PI ;
}

float FirstPersonCamera::get_beta_from_camera(Camera* cam) {
    float dirX = cam->getLookX() - cam->getPosX();
    float dirY = cam->getLookY() - cam->getPosY();
    float dirZ = cam->getLookZ() - cam->getPosZ();

    float len = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    if (len < 1e-6f) {
        return 0.0f;
    }

    float sinBeta = dirY / len;
    if (sinBeta > 1.0f) sinBeta = 1.0f;
    if (sinBeta < -1.0f) sinBeta = -1.0f;
    return asin(sinBeta) * 180.0f / M_PI;
}

void FirstPersonCamera::update_camera_LookAt() {
	// Graus para radianos
	float alpha_rad = alpha * M_PI / 180.0f;
	float beta_rad = beta * M_PI / 180.0f;

	// Direction vector from yaw (alpha) and pitch (beta).
	float dirX = sin(alpha_rad) * cos(beta_rad);
	float dirY = sin(beta_rad);
	float dirZ = cos(alpha_rad) * cos(beta_rad);

    this->setLookX(this->getPosX() + dirX);
    this->setLookY(this->getPosY() + dirY);
    this->setLookZ(this->getPosZ() + dirZ);
}

void FirstPersonCamera::update_camera_Pos() {
	
	// Graus para radianos
	float alpha_rad = alpha * M_PI / 180.0f;
	float beta_rad = beta * M_PI / 180.0f;

	// Vetor direção: d = (sin(alpha)cos(beta), sin(beta), cos(alpha)cos(beta))
	float dirX = sin(alpha_rad) * cos(beta_rad);
    float dirY = sin(beta_rad);
	float dirZ = cos(alpha_rad) * cos(beta_rad);

	// Vetor direção perpendicular a d: r = up × d = (cos(alpha)cos(beta), 0, -sin(alpha)cos(beta))
	float rightX = cos(alpha_rad) * cos(beta_rad);
	float rightZ = -sin(alpha_rad) * cos(beta_rad);
	
	if (keyW) {
        this->setPosX(this->getPosX() + dirX * move_speed);
        this->setPosY(this->getPosY() + dirY * move_speed);
        this->setPosZ(this->getPosZ() + dirZ * move_speed);
	}
	if (keyS) {
		this->setPosX(this->getPosX() - dirX * move_speed);
        this->setPosY(this->getPosY() - dirY * move_speed);
		this->setPosZ(this->getPosZ() - dirZ * move_speed);
	}
	
	if (keyA) {
        this->setPosX(this->getPosX() + rightX * move_speed);
        this->setPosZ(this->getPosZ() + rightZ * move_speed);
	}
	if (keyD) {
		this->setPosX(this->getPosX() - rightX * move_speed);
        this->setPosZ(this->getPosZ() - rightZ * move_speed);
	}
}

void FirstPersonCamera::update_move_speed(float s) {
    move_speed += s;
}

void FirstPersonCamera::set_alpha(float a) { alpha = a; }
void FirstPersonCamera::set_beta(float b) { beta = b; }
void FirstPersonCamera::set_move_speed(float s) { move_speed = s; }
void FirstPersonCamera::set_keyW(bool state) { keyW = state; }
void FirstPersonCamera::set_keyA(bool state) { keyA = state; }
void FirstPersonCamera::set_keyS(bool state) { keyS = state; }
void FirstPersonCamera::set_keyD(bool state) { keyD = state; }
void FirstPersonCamera::set_tracking(float t) { tracking = t; }
void FirstPersonCamera::set_startX(float x) { startX = x; }
void FirstPersonCamera::set_startY(float y) { startY = y; }

float FirstPersonCamera::get_alpha() { return alpha; }
float FirstPersonCamera::get_beta() { return beta; }
float FirstPersonCamera::get_move_speed() { return move_speed; }
bool FirstPersonCamera::get_keyW() { return keyW; }
bool FirstPersonCamera::get_keyA() { return keyA; }
bool FirstPersonCamera::get_keyS() { return keyS; }
bool FirstPersonCamera::get_keyD() { return keyD; }
float FirstPersonCamera::get_tracking() { return tracking; }
float FirstPersonCamera::get_startX() { return startX; }
float FirstPersonCamera::get_startY() { return startY; }


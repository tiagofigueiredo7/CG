#include "engine/structs/camera/ThirdPersonCamera.hpp"

ThirdPersonCamera::ThirdPersonCamera() : Camera() {
    

}

ThirdPersonCamera::ThirdPersonCamera(Camera* cam) : Camera(*cam) {
    
}
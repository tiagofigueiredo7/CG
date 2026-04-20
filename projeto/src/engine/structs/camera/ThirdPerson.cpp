#include "engine/structs/camera/ThirdPerson.hpp"

ThirdPersonCamera::ThirdPersonCamera() : Camera() {
    

}

ThirdPersonCamera::ThirdPersonCamera(Camera* cam) : Camera(*cam) {
    
}
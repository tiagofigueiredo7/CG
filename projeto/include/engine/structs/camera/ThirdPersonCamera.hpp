#ifndef THIRDPERSONCAMERA_HPP
#define THIRDPERSONCAMERA_HPP

#include "Camera.hpp"

class ThirdPersonCamera : public Camera {
    private:

    public:
        ThirdPersonCamera();
        ThirdPersonCamera(Camera* cam);
};


#endif
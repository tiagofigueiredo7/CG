#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include "Camera.hpp"

class FirstPersonCamera : public Camera {
    private:
        

    public:
        FirstPersonCamera();
        FirstPersonCamera(Camera* cam);

        void update_camera();

};


#endif
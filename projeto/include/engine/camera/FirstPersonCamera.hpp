#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include "Camera.hpp"

class FirstPersonCamera : public Camera {
    private:
        float alpha;      // Rotation angle (degrees)
        float move_speed;  // Speed of movement

        float startX;
        float startY;

        float tracking;

        bool keyW;
        bool keyA;
        bool keyS;
        bool keyD;
        

    public:
        FirstPersonCamera();
        FirstPersonCamera(Camera* cam);

        float get_alpha_from_camera();

        void update_camera_Pos();
        void update_camera_LookAt();
        void update_move_speed(float s);

        void set_alpha(float a);
        void set_move_speed(float s);
        void set_keyW(bool state);
        void set_keyA(bool state);
        void set_keyS(bool state);
        void set_keyD(bool state);
        void set_tracking(float t);
        void set_startX(float x);
        void set_startY(float y);

        float get_alpha();
        float get_move_speed();
        bool get_keyW();
        bool get_keyA();
        bool get_keyS();
        bool get_keyD();
        float get_tracking();
        float get_startX();
        float get_startY();

};


#endif
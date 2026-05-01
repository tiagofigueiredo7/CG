#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include "Camera.hpp"

class FirstPersonCamera : public Camera {
    private:
        float alpha;      // Angulo Yaw/alpha (degrees) : Rotação horizontal
        float beta;       // Angulo Pitch/beta (degrees) : Rotação vertical
        float move_speed;

        float startX;
        float startY;

        float tracking;

        bool keyW;
        bool keyA;
        bool keyS;
        bool keyD;

        float get_alpha_from_camera(Camera* cam);
        float get_beta_from_camera(Camera* cam);
        

    public:
        FirstPersonCamera();
        FirstPersonCamera(Camera* cam);

        void update_camera_Pos();
        void update_camera_LookAt();
        void update_move_speed(float s);

        void set_alpha(float a);
        void set_beta(float b);
        void set_move_speed(float s);
        void set_keyW(bool state);
        void set_keyA(bool state);
        void set_keyS(bool state);
        void set_keyD(bool state);
        void set_tracking(float t);
        void set_startX(float x);
        void set_startY(float y);

        float get_alpha();
        float get_beta();
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
#ifndef ORBITALCAMERA_HPP
#define ORBITALCAMERA_HPP

#include "Camera.hpp"

class OrbitalCamera : public Camera {
    private:
        //Coordenadas esféricas
        float alpha_coord;
        float beta_coord;
        float radius_coord;
        float zoom_speed;

    public:
        OrbitalCamera();
        OrbitalCamera(Camera* cam);

        void update_cartesian_coordinates();

        void update_alpha(float a);
        void update_beta(float b);
        void update_radius(float r);
        void update_zoom_speed(float z);

        void set_alpha(float a);
        void set_beta(float b);
        void set_radius(float r);
        void set_zoom_speed(float z);

        float get_alpha();
        float get_beta();
        float get_radius();
        float get_zoom_speed();
};


#endif
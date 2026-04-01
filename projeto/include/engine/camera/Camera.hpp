#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math.h>

class Camera {
    private:
        // Camera position
        float posX;
        float posY;
        float posZ;

        // Camera lookAt
        float lookX;
        float lookY;
        float lookZ;     

        // Camera up vector
        float upX;
        float upY;
        float upZ; 

    public:
        Camera();
        Camera(Camera* cam);
        virtual ~Camera();

        // Getters
        float getPosX();
        float getPosY();
        float getPosZ();

        float getLookX();
        float getLookY();
        float getLookZ();

        float getUpX();
        float getUpY();
        float getUpZ();

        // Setters
        void setPosX(float x);
        void setPosY(float y);
        void setPosZ(float z);

        void setLookX(float x);
        void setLookY(float y);
        void setLookZ(float z);

        void setUpX(float x);
        void setUpY(float y);
        void setUpZ(float z);
        

};


#endif
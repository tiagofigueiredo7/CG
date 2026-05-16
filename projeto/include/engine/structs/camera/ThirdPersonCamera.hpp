#ifndef THIRDPERSONCAMERA_HPP
#define THIRDPERSONCAMERA_HPP

#include "Camera.hpp"
#include "engine/structs/Group.hpp"

class ThirdPersonCamera : public Camera {
    private:

        //target
        Group* target;
        int targetIndex;
        int numPlayers;

        float distance;
        float height;
        float lookHeight;

    public:
        ThirdPersonCamera(int playersCount);
        ThirdPersonCamera(Camera* cam, int playersCount);

        void update_camera_Pos();
        void update_camera_LookAt();

        int getTargetIndex();
        void incrementTargetIndex();
        void setTarget(Group* target);
        Group* getTarget();

        float getDistance();
        float getHeight();
        float getLookHeight();
        void setDistance(float value);
        void setHeight(float value);
        void setLookHeight(float value);
};


#endif
#ifndef DIRECTIONAL_HPP
#define DIRECTIONAL_HPP

#include "Light.hpp"

class Directional : public Light {
    private:
        float dirX;
        float dirY;
        float dirZ;

    public:
        Directional(float x, float y, float z);

        float getDirX();
        float getDirY();
        float getDirZ();

        void setDirX(float x);
        void setDirY(float y);
        void setDirZ(float z);
};

#endif

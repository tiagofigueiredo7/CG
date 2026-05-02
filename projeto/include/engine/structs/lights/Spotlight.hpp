#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include "Light.hpp"

class Spotlight : public Light {
    private:
        float posX;
        float posY;
        float posZ;

        float dirX;
        float dirY;
        float dirZ;

        float cutoff;

    public:
        Spotlight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff);

        float getDirX();
        float getDirY();
        float getDirZ();

        void setDirX(float x);
        void setDirY(float y);
        void setDirZ(float z);

        float getPosX();
        float getPosY();
        float getPosZ();

        void setPosX(float x);
        void setPosY(float y);
        void setPosZ(float z);

        float getCutoff();
        void setCutoff(float cutoff);
};

#endif

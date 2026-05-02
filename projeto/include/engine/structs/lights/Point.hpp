#ifndef POINT_HPP
#define POINT_HPP

#include "Light.hpp"


class Point : public Light {
    private:
        float posX;
        float posY;
        float posZ;

    public:
        Point(float x, float y, float z);

        float getPosX();
        float getPosY();
        float getPosZ();

        void setPosX(float x);
        void setPosY(float y);
        void setPosZ(float z);
        

};


#endif
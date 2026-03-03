#ifndef ROTATE_HPP
#define ROTATE_HPP

#include "engine/Transformation.hpp"

class Rotate : public Transformation {

    private:
        float angle;

    public:
        Rotate(float x, float y, float z, float angle);
        Rotate();

        float getAngle();

        void setAngle(float novoAngle);
    
};


#endif
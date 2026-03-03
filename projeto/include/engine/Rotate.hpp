#ifndef ROTATE_HPP
#define ROTATE_HPP

#include "engine/Transformation.hpp"

class Rotate : public Transformation {

    private:
        float angle;

    public:
        Rotate();

        float getAngle();

        void setAngle();
    
};


#endif
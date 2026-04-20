#ifndef TIMEDFULLROTATE_HPP
#define TIMEDFULLROTATE_HPP

#include "Transformation.hpp"

class TimedFullRotate : public Transformation {

    private:
        float time;

    public:
        TimedFullRotate(float x, float y, float z, float time);
        TimedFullRotate();

        float getTime();

        void setTime(float novoTime);
    
};


#endif
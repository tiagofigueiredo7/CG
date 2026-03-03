#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

class Transformation {
    private:
        float x;
        float y;
        float z;

    public:
        Transformation();

        float getX();
        float getY();
        float getZ();

        void setX(float novoX);
        void setY(float novoY);
        void setZ(float novoZ);

};


#endif
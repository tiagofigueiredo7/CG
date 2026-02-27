#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

typedef struct Transformation {
    float x;
    float y;
    float z;
    float angle;
    int type; // 0 for translation, 1 for rotation, 2 for scaling
} transformation;

#endif
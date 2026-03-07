#include "engine/transformations/Curve.hpp"

Curve::Curve(bool align, float time) {
    this->align = align;
    this->time = time;
    this->points = vector<float*>();
}

Curve::Curve() {
    this->align = false;
    this->time = 0;
    this->points = vector<float*>();
}

Curve::~Curve() {
    for (float* f: this->getPoints()){
        free(f);
    }
}

bool Curve::getAlign(){ return align; }
float Curve::getTime(){ return time; }
vector<float*> Curve::getPoints(){ return points; }

void Curve::setAlign(bool novoAlign){ this->align = novoAlign; }
void Curve::setTime(float novoTime){ this->time = novoTime; }
void Curve::addPoint(float* arr){ this->points.push_back(arr); }

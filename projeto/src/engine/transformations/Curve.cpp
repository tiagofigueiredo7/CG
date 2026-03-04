#include "engine/transformations/Curve.hpp"

Curve::Curve(bool alygn, float time) {
    this->alygn = alygn;
    this->time = time;
    this->points = vector<float*>();
}

Curve::Curve() {
    this->alygn = false;
    this->time = 0;
    this->points = vector<float*>();
}

Curve::~Curve() {
    for (float* f: this->getPoints()){
        free(f);
    }
}

bool Curve::getAlygn(){ return alygn; }
float Curve::getTime(){ return time; }
vector<float*> Curve::getPoints(){ return points; }

void Curve::setAlygn(bool novoAlygn){ this->alygn = novoAlygn; }
void Curve::setTime(float novoTime){ this->time = novoTime; }
void Curve::addPoint(float* arr){ this->points.push_back(arr); }

#include "engine/transformations/Curve.hpp"

Curve::Curve(bool alygn, float time, vector<float*>* points) {
    this->alygn = alygn;
    this->time = time;
    this->points = *points;
}

Curve::Curve() {
    this->alygn = false;
    this->time = 0;
    this->points = vector<float*>();
}

bool Curve::getAlygn(){ return alygn; }
float Curve::getTime(){ return time; }
vector<float*> Curve::getPoints(){ return points; }

void Curve::setAlygn(bool novoAlygn){ this->alygn = novoAlygn; }
void Curve::setTime(float novoTime){ this->time = novoTime; }
void Curve::setPoints(vector<float*>* novoPoints){ this->points = *novoPoints; }

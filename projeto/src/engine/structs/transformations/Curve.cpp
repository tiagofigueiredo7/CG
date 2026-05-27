#include "engine/structs/transformations/Curve.hpp"

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
const vector<float*>& Curve::getPoints() { return points; }

void Curve::setAlign(bool novoAlign){ this->align = novoAlign; }
void Curve::setTime(float novoTime){ this->time = novoTime; }
void Curve::addPoint(float* arr){ this->points.push_back(arr); }


void Curve::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
	for (int i = 0; i < 3; i++){
		float a[4], p[4] = {p0[i],p1[i],p2[i],p3[i]};
		multMatrixVector((float*)m,p,a); 
		pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3]; // posição do ponto na curva
		deriv[i] = (3 * powf(t, 2.0)) * a[0] + (2*t) * a[1] + a[2]; // vetor tangente à curva
	}
}


void Curve::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
    vector<float*> p = this->getPoints();
    int point_count = points.size();
	float t = gt * point_count; 
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	int indices[4]; 
	indices[0] = (index + point_count-1)%point_count;	
	indices[1] = (indices[0]+1)%point_count;
	indices[2] = (indices[1]+1)%point_count; 
	indices[3] = (indices[2]+1)%point_count;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}


void Curve::renderCatmullRomCurve() {
	glBegin(GL_LINE_LOOP);
	float gt = 0, pos[3], deriv[3];
	for (int i = 0; i<100; i++) {
		getGlobalCatmullRomPoint(gt, pos, deriv);
		glVertex3f(pos[0], pos[1], pos[2]);
		gt += 0.01;
	}
	glEnd();
}

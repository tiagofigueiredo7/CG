// Biblioteca do glut
#ifdef __APPLE__

#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif

// Bibliotcas uteis
#include <string>
#include <iostream>
#include <fstream>

#include <tinyxml2.h>
#include <vector>
#include <math.h>
#include <sstream>

// Nossas bibliotecas
#include "../utils/utils.hpp"

using namespace std;
using namespace utils;
using namespace tinyxml2;

int main(int argc, char** argv);

void changeSize(int w, int h);

void renderScene(void);

void processXML(char* file);

void createModel(char* model_file);

#ifndef ENGINE_HPP
#define ENGINE_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glut.h>    // Para correr em Linux
#endif

// Bibliotecas uteis
#include <string>
#include <iostream>
#include <fstream>

#include <tinyxml2.h>
#include <vector>
#include <math.h>
#include <sstream>

// Bibliotecas locais
#include "utils/util.hpp"

using namespace std;
using namespace util;
using namespace tinyxml2;

int main(int argc, char** argv);

void changeSize(int w, int h);

void renderScene(void);

void processXML(char* file);

void createModel(char* model_file);

#endif

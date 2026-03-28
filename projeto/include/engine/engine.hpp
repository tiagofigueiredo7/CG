#ifndef ENGINE_HPP
#define ENGINE_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

// Bibliotecas uteis
#include <typeinfo> // Biblioteca com método "typeid" semelhante a "instanceof"
#include <stdlib.h>

#include <vector>
#include <math.h>

// Bibliotecas locais
#include "utils/util.hpp"
#include "engine/Data.hpp"

using namespace std;
using namespace util;

int main(int argc, char** argv);

void changeSize(int w, int h);

void renderScene(void);

void renderGroup(Group& g);

void createModel(int init, int count, GLuint* buffer);

#endif
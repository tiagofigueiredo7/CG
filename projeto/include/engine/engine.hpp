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
#include "engine/process_input.hpp"
#include "engine/Data.hpp"

using namespace std;
using namespace util;

int main(int argc, char** argv);

void update_camera(int value);

void processMouseButtons(int button, int state, int xx, int yy);

void processMouseMotion(int xx, int yy);

void processKeys(unsigned char c, int xx, int yy);

void processKeysUp(unsigned char key, int xx, int yy);

void processSpecialKeys(int key, int xx, int yy);

void changeSize(int w, int h);

void renderScene(void);

#endif
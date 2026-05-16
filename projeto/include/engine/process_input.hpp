#ifndef PROCESS_INPUT_HPP
#define PROCESS_INPUT_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

// Bibliotecas locais
#include "engine/structs/Data.hpp"

void processMouseButtons_aux(int button, int state, int xx, int yy, Data* store);

void processMouseMotion_aux(int xx, int yy, Data* store);

void processKeys_aux(unsigned char c, int xx, int yy, Data* store);

void processKeys_Fpc_aux(unsigned char c, int xx, int yy, FirstPersonCamera* fpc);

void processKeys_Orb_aux(unsigned char c, int xx, int yy, OrbitalCamera* oc);

void processKeysUp_aux(unsigned char key, int xx, int yy, Data* store);

void processSpecialKeys_aux(int key, int xx, int yy, Data* store);

void processKeys_Tpc_aux(unsigned char c, int xx, int yy, ThirdPersonCamera* tpc);


#endif
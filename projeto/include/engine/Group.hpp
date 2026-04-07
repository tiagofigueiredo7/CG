#ifndef GROUP_HPP
#define GROUP_HPP

// Biblioteca do glut
#ifdef __APPLE__ // Para correr em MacOS
#include <GLUT/glut.h>  // Para correr em MacOS
#else
#include <GL/glew.h>
#include <GL/glut.h>    // Para correr em Linux
#endif

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

#include "engine/transformations/Transformation.hpp"
#include "engine/transformations/Translate.hpp"
#include "engine/transformations/Rotate.hpp"
#include "engine/transformations/Scale.hpp"
#include "engine/transformations/Curve.hpp"
#include "engine/transformations/TimedFullRotate.hpp"


class Group {
    private:
        vector<Transformation*> transformations;
        vector<Group*> subgroups;

        vector<int> vertices_count;
        GLuint* buffer;

        void createModel(int init, int count, GLuint* buffer);

    public:
        Group();

        ~Group();

        void addTransformation(Transformation* transf);
        void addSubGroup(Group* subgroup);
        void addVerticeCount(int count);

        vector<Transformation*> getTransformations();
        vector<Group*> getSubGroups();
        vector<int> getVerticesCount();
        GLuint* getBuffer();

        void renderGroup();

};


#endif
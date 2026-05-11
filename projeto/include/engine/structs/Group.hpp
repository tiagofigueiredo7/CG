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

#include "engine/structs/transformations/Transformation.hpp"
#include "engine/structs/transformations/Translate.hpp"
#include "engine/structs/transformations/Rotate.hpp"
#include "engine/structs/transformations/Scale.hpp"
#include "engine/structs/transformations/Curve.hpp"
#include "engine/structs/transformations/TimedFullRotate.hpp"
#include "engine/structs/Material.hpp"

typedef struct pos {
    float x;
    float y;
    float z;
} Pos;


class Group {
    private:
        vector<Transformation*> transformations;
        vector<Group*> subgroups;

        vector<int> vertices_count;
        vector<Material*> materials;
        vector<GLuint*> texturesIDs;
        
        GLuint* buffers;

        bool isPlayer;
        string playerName;
        Pos globalPosition;


        void createModel(int init, int count, GLuint* buffers);
        void createModel_wTexture(int init, int count, GLuint* buffers, GLuint* textureID);

    public:
        Group();

        ~Group();

        void addTransformation(Transformation* transf);
        void addMaterial(Material* material);
        void addSubGroup(Group* subgroup);
        void addVerticeCount(int count);
        void addTextureID(GLuint* id);

        vector<Transformation*> getTransformations();
        vector<Group*> getSubGroups();
        vector<int> getVerticesCount();
        vector<GLuint*> getTexturesIDs();
        GLuint* getBuffers();
        vector<Material*> getMaterials();

        void renderGroup(bool flag);

        bool getIsPlayer();
        void setIsPlayer(bool isPlayer);
        string getPlayerName();
        void setPlayerName(string playerName);
        Pos getGlobalPosition();
        void setGlobalPosition(float x, float y, float z);

};


#endif
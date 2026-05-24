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

#include "engine/structs/transformations/Transformation.hpp"
#include "engine/structs/transformations/Translate.hpp"
#include "engine/structs/transformations/Rotate.hpp"
#include "engine/structs/transformations/Scale.hpp"
#include "engine/structs/transformations/Curve.hpp"
#include "engine/structs/transformations/TimedFullRotate.hpp"
#include "engine/structs/Material.hpp"
#include "engine/structs/Frustum.hpp"
#include "utils/util.hpp"

using namespace std;
using namespace util;

typedef struct pos {
    float x;
    float y;
    float z;
} Pos;


class Group {
    private:
        vector<Transformation*> transformations;
        vector<Group*> subgroups;

        // Dados dos modelos
        vector<int> vertices_count;
        vector<Material*> materials;
        vector<GLuint*> texturesIDs;
        vector<float> raios_Esferas; // vetor para armazenar os raios das esferas circunscritas aos modelos
        vector<float> raios_Esferas_world; // vetor para armazenar os raios globais dos modelos
        vector<Pos> modelCenters; // centros locais dos modelos para culling / Local
        vector<Pos> modelCenters_world; // centros mundiais dos modelos para culling / World

        GLuint* buffers;

        bool isPlayer;
        string playerName;
        Pos globalPosition;


        void createModel(int init, int count, GLuint* buffers);
        void createModel_wTexture(int init, int count, GLuint* buffers, GLuint* textureID);

    public:
        Group();

        ~Group();

        void renderGroup(bool renderExtraLines, Frustum* f);
        void updatePlayersWorldPositions();

        void addTransformation(Transformation* transf);
        void addMaterial(Material* material);
        void addSubGroup(Group* subgroup);
        void addVerticeCount(int count);
        void addTextureID(GLuint* id);
        void addRaioEsfera(float raio);
        void addRaioEsfera_world(float raio);
        void addModelCenter(Pos c);
        void addModelCenter_world(Pos c);

        vector<Transformation*> getTransformations();
        vector<Group*> getSubGroups();
        vector<int> getVerticesCount();
        vector<GLuint*> getTexturesIDs();
        vector<float> getRaiosEsferas();
        vector<float> getRaiosEsferas_world();
        vector<Pos> getModelCenters();
        GLuint* getBuffers();
        vector<Material*> getMaterials();
        vector<Pos> getModelCenters_world();
        bool getIsPlayer();
        string getPlayerName();

        void setIsPlayer(bool isPlayer);
        void setPlayerName(string playerName);
        Pos getGlobalPosition();
        void setGlobalPosition(float x, float y, float z);
        void setModelCenters_world(Pos p, int index);
        void setRaiosEsferas_world(float raio, int index);

};


#endif
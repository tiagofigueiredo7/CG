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
        vector<Point3D> modelCenters; // centros locais dos modelos para culling / Local
        vector<Point3D> modelCenters_world; // centros mundiais dos modelos para culling / World

        GLuint* buffers;

        bool isPlayer;
        string playerName;
        Point3D globalPosition;


        void createModel(int init, int count, GLuint* buffers, GLuint* textureID);

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
        void addModelCenter(Point3D c);
        void addModelCenter_world(Point3D c);

        const vector<Transformation*>& getTransformations();
        const vector<Group*>& getSubGroups();
        const vector<int>& getVerticesCount();
        const vector<GLuint*>& getTexturesIDs();
        const vector<float>& getRaiosEsferas();
        const vector<float>& getRaiosEsferas_world();
        const vector<Point3D>& getModelCenters();
        GLuint* getBuffers();
        const vector<Material*>& getMaterials();
        const vector<Point3D>& getModelCenters_world();
        bool getIsPlayer();
        string getPlayerName();

        void setIsPlayer(bool isPlayer);
        void setPlayerName(string playerName);
        Point3D getGlobalPosition();
        void setGlobalPosition(float x, float y, float z);
        void setModelCenters_world(Point3D p, int index);
        void setRaiosEsferas_world(float raio, int index);

};


#endif
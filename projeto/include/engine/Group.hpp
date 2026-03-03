#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "engine/Transformation.hpp"
#include "engine/Translate.hpp"
#include "engine/Rotate.hpp"
#include "engine/Scale.hpp"


class Group {
    private:
        vector<Transformation*> transformations;
        vector<char *> model_files;
        vector<Group*> subgroups;

    public:
        Group();

        void addTransformation(Transformation* transf);
        void addModelFile(char* model_file);
        void addSubGroup(Group* subgroup);

        vector<Transformation*> getTransformations();
        vector<char *> getModelFiles();
        vector<Group*> getSubGroups();

        void print(int depth = 0);
};


#endif
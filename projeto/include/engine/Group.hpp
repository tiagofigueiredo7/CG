#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "engine/transformation.hpp"


class Group {
    private:
        vector<transformation> transformations;
        vector<char *> model_files;
        vector<Group*> subgroups;

    public:
        Group();

        void addTransformation(transformation transf);
        void addModelFile(char* model_file);
        void addSubGroup(Group* subgroup);

        vector<transformation> getTransformations();
        vector<char *> getModelFiles();
        vector<Group*> getSubGroups();

        void print(int depth = 0);
};


#endif
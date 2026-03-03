#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <vector>
#include <iostream>
#include <tinyxml2.h>

#include "engine/Group.hpp"

using namespace std;
using namespace tinyxml2;

class Data {
    private:
        // Camera position
        float posX;
        float posY;
        float posZ;

        // Camera lookAt
        float lookX;
        float lookY;
        float lookZ;     

        // Camera up vector
        float upX;
        float upY;
        float upZ;           

        // Perspective parameters
        float fov;
        float nearPlane;
        float farPlane;

        // Window size parameters
        int width;
        int height;      

        // Model files and transformations
        Group* group;

        // Group element parser
        void parseGroupField(Group& g, XMLElement* group);

    public:
        Data();

        ~Data();

        // Parser XML
        void parseXML(char* file);

        // Getters
        float getPosX();
        float getPosY();
        float getPosZ();

        float getLookX();
        float getLookY();
        float getLookZ();

        float getUpX();
        float getUpY();
        float getUpZ();

        float getFov();
        float getNearPlane();
        float getFarPlane();

        int getWidth();
        int getHeight();

        Group* getGroup();

        // Setters
        void setPosX(float x);
        void setPosY(float y);
        void setPosZ(float z);

        void setLookX(float x);
        void setLookY(float y);
        void setLookZ(float z);

        void setUpX(float x);
        void setUpY(float y);
        void setUpZ(float z);

        void setFov(float fov);
        void setNearPlane(float near);
        void setFarPlane(float far);

        void setWidth(int w);
        void setHeight(int h);

        void setGroup(Group* g);
};



#endif
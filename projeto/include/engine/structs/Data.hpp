#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <vector>
#include <tinyxml2.h>
#include <IL/il.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "engine/structs/Group.hpp"
#include "engine/structs/camera/Camera.hpp"
#include "engine/structs/camera/OrbitalCamera.hpp"
#include "engine/structs/camera/FirstPersonCamera.hpp"
#include "engine/structs/camera/ThirdPerson.hpp"
#include "engine/structs/lights/Light.hpp"
#include "engine/structs/lights/Directional.hpp"
#include "engine/structs/lights/Point.hpp"
#include "engine/structs/lights/Spotlight.hpp"

using namespace std;
using namespace tinyxml2;

class Data {
    private:       
        // Camera
        Camera* camera;

        // Lights
        vector<Light*> lights;

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
        void parseCameraField(XMLElement* camera);
        void parseGroupField(Group& g, XMLElement* group);
        void parseLightsField(XMLElement* lights);

        void fill_Buffer(Group& g, vector<char*>& arr);
        int loadTexture(string s);

    public:
        Data();

        ~Data();

        // Parser XML
        void parse_Window_Information(char* file);
        void parseXML(char* file);

        // Getters
        float getFov();
        float getNearPlane();
        float getFarPlane();

        int getWidth();
        int getHeight();

        Group* getGroup();
        Camera* getCamera();

        // Setters
        void setFov(float fov);
        void setNearPlane(float near);
        void setFarPlane(float far);

        void setWidth(int w);
        void setHeight(int h);

        void setGroup(Group* g);
        void setCamera(Camera* c);

        vector<Light*> getLights();
        void addLight(Light* light);
};



#endif
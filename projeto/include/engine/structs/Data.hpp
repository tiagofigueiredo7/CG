#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <vector>
#include <tinyxml2.h>
#include <IL/il.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "utils/util.hpp"
#include "engine/structs/Group.hpp"
#include "engine/structs/camera/Camera.hpp"
#include "engine/structs/camera/OrbitalCamera.hpp"
#include "engine/structs/camera/FirstPersonCamera.hpp"
#include "engine/structs/lights/Light.hpp"
#include "engine/structs/lights/Directional.hpp"
#include "engine/structs/lights/Point.hpp"
#include "engine/structs/lights/Spotlight.hpp"
#include "engine/structs/Frustum.hpp"
#include "engine/structs/FPS.hpp"

using namespace std;
using namespace util;
using namespace tinyxml2;

class Data {
    private:

        // Camera
        Camera* camera;

        // Frustum
        Frustum* frustum;

        // Lights
        vector<Light*> lights;

        // Perspective parameters
        float fov;
        float nearPlane;
        float farPlane;

        // Window size parameters
        int width;
        int height;    
        
        // Flag para renderizar ou não a trajetória da curva e eixos
        bool renderExtraLines;
        bool renderFrustum;

        // Nodo raiz da hierarquia de grupos
        Group* group;

        // Targets
        vector<Group*> targets;

        // FPS counter
        FPS* fpsCounter;

        // Group element parser
        void parseCameraField(XMLElement* camera);
        void parseGroupField(Group& g, XMLElement* group);
        void parseLightsField(XMLElement* lights);

        void fill_Buffer(Group& g, vector<char*>& arr);
        int loadTexture(string s);

    public:
        Data();

        ~Data();

        // Extra Draws
        void drawExtraLines();

        // Axis
        void drawAxis();

        // Frustum
        Frustum* getFrustum();
        void updateFrustum();
        void drawFrustum();

        // Lights
        void initLights();
        void executeLights();

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

        const vector<Light*>& getLights();
        void addLight(Light* light);

        void setRenderExtraLines(bool flag);
        bool getRenderExtraLines();
        void setRenderFrustum(bool flag);
        bool getRenderFrustum();

        const vector<Group*>& getTargets();
        void addTarget(Group* target);
        Group* getTargetByIndex(int id);

        // FPS and Camera
        void updateFPS();
        string getCameraName();
        string getWindowTitle();
};



#endif
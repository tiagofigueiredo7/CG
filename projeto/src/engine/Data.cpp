#include "engine/Data.hpp"

// Construtores

Data::Data() {
    // Vlores Padrão
    posX = 0.0f;
    posY = 0.0f;
    posZ = 5.0f;

    lookX = 0.0f;
    lookY = 0.0f;
    lookZ = -1.0f;

    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;

    fov = 45.0f;
    nearPlane = 1.0f;
    farPlane = 1000.0f;

    width = 800;
    height = 800;

    group = nullptr;
}

// Destrutor

Data::~Data(){
    delete this->group;
}

// Parser

void Data::parseXML(char* file) {
    // Carregar documento XML
    XMLDocument doc;
    XMLError result = doc.LoadFile(file);
    
    if (result != XML_SUCCESS) {
        cerr << "Erro ao carregar XML: " << result << std::endl;
        return;
    }
    
    // Obter elemento raiz <world>
    XMLElement* world = doc.FirstChildElement("world");
    if (!world) {
        cerr << "Elemento <world> não encontrado!" << std::endl;
        return;
    }
    
    // Ler janela
    XMLElement* window = world->FirstChildElement("window");
    if (window) {
        this->setWidth(window->IntAttribute("width"));
        this->setHeight(window->IntAttribute("height"));
    }
    
    // Ler camara
    XMLElement* camera = world->FirstChildElement("camera");
    if (camera) {
        
        // Position
        XMLElement* position = camera->FirstChildElement("position");
        if (position) {
            this->setPosX(position->FloatAttribute("x"));
            this->setPosY(position->FloatAttribute("y"));
            this->setPosZ(position->FloatAttribute("z"));
        }
        
        // LookAt
        XMLElement* lookAt = camera->FirstChildElement("lookAt");
        if (lookAt) {
            this->setLookX(lookAt->FloatAttribute("x"));
            this->setLookY(lookAt->FloatAttribute("y"));
            this->setLookZ(lookAt->FloatAttribute("z"));
        }
        
        // Up (valores padrão se não existir)
        XMLElement* up = camera->FirstChildElement("up");
        if (up) {
            this->setUpX(up->FloatAttribute("x", 0.0f));
            this->setUpY(up->FloatAttribute("y", 1.0f));
            this->setUpZ(up->FloatAttribute("z", 0.0f));
        }
        
        // Projection
        XMLElement* projection = camera->FirstChildElement("projection");
        if (projection) {
            this->setFov(projection->FloatAttribute("fov", 60.0f));
            this->setNearPlane(projection->FloatAttribute("near", 1.0f));
            this->setFarPlane(projection->FloatAttribute("far", 1000.0f));
        }
    }

    Group* main_group = new Group();
    this->parseGroupField(*main_group, world->FirstChildElement("group"));
    this->setGroup(main_group);
}

void Data::parseGroupField(Group& g, XMLElement* group) {
    XMLElement* transf = group->FirstChildElement("transform");

    if (transf){
        XMLElement* prox = transf->FirstChildElement();
        while (prox != nullptr){

            Transformation* t = nullptr;

            const char* nome = prox->Name();
            float x = prox->FloatAttribute("x");
            float y = prox->FloatAttribute("y");
            float z = prox->FloatAttribute("z");
            float angle = 0.0f;
            if (strcmp(nome, "rotate") == 0) {
                angle = prox->FloatAttribute("angle");
            }

            if (strcmp(nome, "translate") == 0) t = new Translate(x,y,z);
            else if (strcmp(nome, "scale") == 0) t = new Scale(x,y,z);
            else if (strcmp(nome, "rotate") == 0) t = new Rotate(x,y,z,angle);
            else {
                cerr << "ERRO: Transformação desconhecida!";
                return;
            }

            g.addTransformation(t);

            prox = prox->NextSiblingElement();
        }
    }

    XMLElement* models = group->FirstChildElement("models");

    if (models){
        XMLElement* model = models->FirstChildElement("model");
            while(model != nullptr) {
            const char* file = model->Attribute("file");
            if (file) {
                g.addModelFile(strdup(file));
            }
            model = model->NextSiblingElement("model");
        }
    }

    XMLElement* child_group = group->FirstChildElement("group");

    if (child_group){
        while(child_group != nullptr){
            Group* child = new Group(); 
            this->parseGroupField(*child, child_group);
            g.addSubGroup(child);
            child_group = child_group->NextSiblingElement("group");
        }
    }
}

// Getters

float Data::getPosX() { return posX; }

float Data::getPosY() { return posY; }

float Data::getPosZ() { return posZ; }

float Data::getLookX() { return lookX; }

float Data::getLookY() { return lookY; }

float Data::getLookZ() { return lookZ; }

float Data::getUpX() { return upX; }

float Data::getUpY() { return upY; }

float Data::getUpZ() { return upZ; }

float Data::getFov() { return fov; }

float Data::getNearPlane() { return nearPlane; }

float Data::getFarPlane() { return farPlane; }

int Data::getWidth() { return width; }

int Data::getHeight() { return height; }

Group* Data::getGroup() { return group; }

//Setters

void Data::setPosX(float x) { posX = x; }

void Data::setPosY(float y) { posY = y; }

void Data::setPosZ(float z) { posZ = z; }

void Data::setLookX(float x) { lookX = x; }

void Data::setLookY(float y) { lookY = y; }

void Data::setLookZ(float z) { lookZ = z; }

void Data::setUpX(float x) { upX = x; }

void Data::setUpY(float y) { upY = y; }

void Data::setUpZ(float z) { upZ = z; }

void Data::setFov(float f) { fov = f; }

void Data::setNearPlane(float near) { nearPlane = near; }

void Data::setFarPlane(float far) { farPlane = far; }

void Data::setWidth(int w) { width = w; }

void Data::setHeight(int h) { height = h; }

void Data::setGroup(Group* g){ group = g; }
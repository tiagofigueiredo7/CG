#include "engine/Data.hpp"

// Construtores

Data::Data() {
    // Vlores Padrão
    fov = 45.0f;
    nearPlane = 1.0f;
    farPlane = 1000.0f;

    width = 800;
    height = 800;

    group = nullptr;
    camera = new Camera();
}

// Destrutor

Data::~Data(){
    delete this->group;
    delete this->camera;
}

// Parser

void Data::parse_Window_Information(char* file) {
    XMLDocument doc;
    XMLError result = doc.LoadFile(file);
    
    if (result != XML_SUCCESS) {
        cerr << "[Erro] Erro ao carregar XML: " << result << endl;
        return;
    }
    
    XMLElement* world = doc.FirstChildElement("world");
    if (!world) {
        cerr << "[Erro] Elemento <world> não encontrado!" << endl;
        return;
    }
    
    XMLElement* window = world->FirstChildElement("window");
    if (window) {
        this->setWidth(window->IntAttribute("width"));
        this->setHeight(window->IntAttribute("height"));
    }

    
}

void Data::parseXML(char* file) {
    // Carregar documento XML
    XMLDocument doc;
    XMLError result = doc.LoadFile(file);
    
    if (result != XML_SUCCESS) {
        cerr << "[Erro] Erro ao carregar XML: " << result << endl;
        return;
    }
    
    // Obter elemento raiz <world>
    XMLElement* world = doc.FirstChildElement("world");
    if (!world) {
        cerr << "[Erro] Elemento <world> não encontrado!" << endl;
        return;
    }
    
    // Ler camara
    XMLElement* camera = world->FirstChildElement("camera");
    if (camera) {
        
        // Position
        XMLElement* position = camera->FirstChildElement("position");
        if (position) {
            this->camera->setPosX(position->FloatAttribute("x"));
            this->camera->setPosY(position->FloatAttribute("y"));
            this->camera->setPosZ(position->FloatAttribute("z"));
        }
        
        // LookAt
        XMLElement* lookAt = camera->FirstChildElement("lookAt");
        if (lookAt) {
            this->camera->setLookX(lookAt->FloatAttribute("x"));
            this->camera->setLookY(lookAt->FloatAttribute("y"));
            this->camera->setLookZ(lookAt->FloatAttribute("z"));
        }
        
        // Up (valores padrão se não existir)
        XMLElement* up = camera->FirstChildElement("up");
        if (up) {
            this->camera->setUpX(up->FloatAttribute("x", 0.0f));
            this->camera->setUpY(up->FloatAttribute("y", 1.0f));
            this->camera->setUpZ(up->FloatAttribute("z", 0.0f));
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


            if (strcmp(nome, "translate") == 0) {
                const char* valor = prox->Attribute("time");
                if (valor == nullptr) {
                    t = new Translate(x,y,z);
                } else {
                    float time = prox->FloatAttribute("time");
                    bool align = prox->BoolAttribute("align");

                    t = new Curve(align, time);

                    XMLElement* point = prox->FirstChildElement("point");
                    while(point != nullptr){
                        float* arr = (float*)malloc(3*sizeof(float));
                        arr[0] = point->FloatAttribute("x");
                        arr[1] = point->FloatAttribute("y");
                        arr[2] = point->FloatAttribute("z");

                        Curve* c = dynamic_cast<Curve*>(t);

                        c->addPoint(arr);

                        point = point->NextSiblingElement("point");
                    }

                }
            }
            else if (strcmp(nome, "scale") == 0) t = new Scale(x,y,z);
            else if (strcmp(nome, "rotate") == 0) {
                const char* valor = prox->Attribute("angle");
                if (valor != nullptr) {
                    float angle = prox->FloatAttribute("angle");
                    t = new Rotate(x,y,z,angle);
                } else {
                    float time = prox->FloatAttribute("time");
                    t = new TimedFullRotate(x,y,z,time);
                }
            } else {
                cerr << "ERRO: Transformação desconhecida!";
                return;
            }

            g.addTransformation(t);

            prox = prox->NextSiblingElement();
        }
    }

    XMLElement* models = group->FirstChildElement("models");

    vector<char* > m_files;

    if (models){
        XMLElement* model = models->FirstChildElement("model");
            while(model != nullptr) {
            const char* file = model->Attribute("file");
            if (file) {
                m_files.push_back(strdup(file));
            }
            model = model->NextSiblingElement("model");
        }
    }

    if (m_files.size() > 0) { // Apenas preencher o buffer se houver modelos para desenhar
        fill_Buffer(g, m_files);
    }
    for (char* c: m_files) free(c);

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

void Data::fill_Buffer(Group& g, vector<char*>& arr){
    int count_aux = 0;
    vector<float> vertices_aux;

    for(char* model_file : arr){
        count_aux = 0;

        string model_path = string("../models/") + model_file;
        ifstream file(model_path);
        if (!file.is_open()){
            cerr << "[ERRO] Erro ao abrir ficheiro: " << model_file << endl;
        }

        string line;
        while(getline(file,line)){
            if (line.empty()) continue;

            istringstream iss(line);
            float x, y, z;
            if (!(iss >> x >> y >> z)) {
                cerr << "[ERRO] Erro ao ler vértice: " << line << endl;
                continue;
            }
            vertices_aux.push_back(x);
            vertices_aux.push_back(y);
            vertices_aux.push_back(z);
            count_aux += 1;
        }

        g.addVerticeCount(count_aux);
        file.close();

    }

    GLuint* buffer = g.getBuffer();

    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glBufferData(GL_ARRAY_BUFFER,vertices_aux.size()*sizeof(float),&vertices_aux[0],GL_STATIC_DRAW);

}

// Getters

float Data::getFov() { return fov; }

float Data::getNearPlane() { return nearPlane; }

float Data::getFarPlane() { return farPlane; }

int Data::getWidth() { return width; }

int Data::getHeight() { return height; }

Group* Data::getGroup() { return group; }

Camera* Data::getCamera() { return camera; }

//Setters

void Data::setFov(float f) { fov = f; }

void Data::setNearPlane(float near) { nearPlane = near; }

void Data::setFarPlane(float far) { farPlane = far; }

void Data::setWidth(int w) { width = w; }

void Data::setHeight(int h) { height = h; }

void Data::setGroup(Group* g){ group = g; }

void Data::setCamera(Camera* c){ camera = c; }
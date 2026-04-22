#include "engine/structs/Data.hpp"

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
    lights = vector<Light*>();
}

// Destrutor

Data::~Data(){
    delete this->group;
    delete this->camera;
    for (Light* light : lights) {
        delete light;
    }
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
    this->parseCameraField(world->FirstChildElement("camera"));

    // Ler luzes
    this->parseLightsField(world->FirstChildElement("lights"));

    // Ler grupo
    Group* main_group = new Group();
    this->parseGroupField(*main_group, world->FirstChildElement("group"));
    this->setGroup(main_group);
}

void Data::parseCameraField(XMLElement* camera) {
    if (!camera) {
        cerr << "[Erro] Elemento <camera> não encontrado!" << endl;
        return;
    }

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

void Data::parseLightsField(XMLElement* lights) {
    if (!lights) {
        cerr << "[Erro] Elemento <lights> não encontrado!" << endl;
        return;
    }

    XMLElement* light = lights->FirstChildElement("light");
    while (light != nullptr) {
        if (strcmp(light->Attribute("type"), "point") == 0) {
            Point* p = new Point(light->FloatAttribute("posX"), light->FloatAttribute("posY"), light->FloatAttribute("posZ"));
            this->addLight(p);
        } else if (strcmp(light->Attribute("type"), "directional") == 0) {
            Directional* d = new Directional(light->FloatAttribute("dirX"), light->FloatAttribute("dirY"), light->FloatAttribute("dirZ"));
            this->addLight(d);
        } else if (strcmp(light->Attribute("type"), "spotlight") == 0) {
            Spotlight* s = new Spotlight(
                light->FloatAttribute("posX"), light->FloatAttribute("posY"), light->FloatAttribute("posZ"),
                light->FloatAttribute("dirX"), light->FloatAttribute("dirY"), light->FloatAttribute("dirZ"),
                light->FloatAttribute("cutoff")
            );
            this->addLight(s);
        } else {
            cerr << "[ERRO] Tipo de luz desconhecido: " << light->Attribute("type") << endl;
        }
        light = light->NextSiblingElement("light");
    }
}

void Data::parseGroupField(Group& g, XMLElement* group) {
    if (!group) {
        cerr << "[Erro] Elemento <group> não encontrado!" << endl;
        return;
    }
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

            XMLElement* texture = model->FirstChildElement("texture");
            if (texture) {
                char *texture_file = strdup(texture->Attribute("file"));
                string texture_path = string("../textures/") + texture_file;
                GLuint* textureID = (GLuint*)malloc(sizeof(GLuint));
                *textureID = loadTexture(texture_path);
                g.addTextureID(textureID);
                free(texture_file);
                
            } else {
                // Se não houver textura, adicionar um ID nulo para manter a consistência
                GLuint* nullTextureID = (GLuint*)malloc(sizeof(GLuint));
                *nullTextureID = 0; // ID nulo
                g.addTextureID(nullTextureID);
            }

            XMLElement* material = model->FirstChildElement("color");
            if (material) {
                Material* m = new Material();
                XMLElement* difuse = material->FirstChildElement("difuse");
                if (difuse) {
                    m->setDifuse(difuse->FloatAttribute("r"), difuse->FloatAttribute("g"), difuse->FloatAttribute("b"), 1.0f);
                }

                XMLElement* ambient = material->FirstChildElement("ambient");
                if (ambient) {
                    m->setAmbient(ambient->FloatAttribute("r"), ambient->FloatAttribute("g"), ambient->FloatAttribute("b"), 1.0f);
                }

                XMLElement* specular = material->FirstChildElement("specular");
                if (specular) {
                    m->setSpecular(specular->FloatAttribute("r"), specular->FloatAttribute("g"), specular->FloatAttribute("b"), 1.0f);
                }

                XMLElement* emissive = material->FirstChildElement("emissive");
                if (emissive) {
                    m->setEmissive(emissive->FloatAttribute("r"), emissive->FloatAttribute("g"), emissive->FloatAttribute("b"), 1.0f);
                }

                XMLElement* shininess = material->FirstChildElement("shininess");
                if (shininess) {
                    m->setShininess(shininess->FloatAttribute("value"));
                }

                g.addMaterial(m);
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

void Data::setCamera(Camera* c){
    if (camera == c) return;
    delete camera;
    camera = c;
}

vector<Light*> Data::getLights() {
    return lights;
}

void Data::addLight(Light* light) {
    if (lights.size() >= 8) {
        cerr << "[Aviso] Número máximo de luzes (8) atingido. Luz não adicionada." << endl;
        return;
    }
    lights.push_back(light);
}

int Data::loadTexture(string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}
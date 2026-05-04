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

    renderCurve = true;
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
        cerr << "[Aviso] Não há luzes definidas!" << endl;
        return;
    }

    XMLElement* light = lights->FirstChildElement("light");
    while (light != nullptr) {
        if (strcmp(light->Attribute("type"), "point") == 0) {
            Point* p = new Point(light->FloatAttribute("posx"), light->FloatAttribute("posy"), light->FloatAttribute("posz"));
            this->addLight(p);
        } else if (strcmp(light->Attribute("type"), "directional") == 0) {
            Directional* d = new Directional(light->FloatAttribute("dirx"), light->FloatAttribute("diry"), light->FloatAttribute("dirz"));
            this->addLight(d);
        } else if (strcmp(light->Attribute("type"), "spotlight") == 0 || strcmp(light->Attribute("type"), "spot") == 0) {
            Spotlight* s = new Spotlight(
                light->FloatAttribute("posx"), light->FloatAttribute("posy"), light->FloatAttribute("posz"),
                light->FloatAttribute("dirx"), light->FloatAttribute("diry"), light->FloatAttribute("dirz"),
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
                XMLElement* difuse = material->FirstChildElement("diffuse");
                if (difuse) {
                    m->setDifuse(difuse->FloatAttribute("R"), difuse->FloatAttribute("G"), difuse->FloatAttribute("B"), 1.0f);
                }

                XMLElement* ambient = material->FirstChildElement("ambient");
                if (ambient) {
                    m->setAmbient(ambient->FloatAttribute("R"), ambient->FloatAttribute("G"), ambient->FloatAttribute("B"), 1.0f);
                }

                XMLElement* specular = material->FirstChildElement("specular");
                if (specular) {
                    m->setSpecular(specular->FloatAttribute("R"), specular->FloatAttribute("G"), specular->FloatAttribute("B"), 1.0f);
                }

                XMLElement* emissive = material->FirstChildElement("emissive");
                if (emissive) {
                    m->setEmissive(emissive->FloatAttribute("R"), emissive->FloatAttribute("G"), emissive->FloatAttribute("B"), 1.0f);
                }

                XMLElement* shininess = material->FirstChildElement("shininess");
                if (shininess) {
                    m->setShininess(shininess->FloatAttribute("value"));
                }

                g.addMaterial(m);
            } else {
                // Se não houver material, adicionar um material padrão para manter a consistência
                Material* defaultMaterial = new Material();
                g.addMaterial(defaultMaterial);
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
    vector<float> vertices_aux;
    vector<float> normals_aux;
    vector<float> texCoords_aux;

    for(char* model_file : arr){
        vector<float> vertices_temp;
        vector<float> normals_temp;
        vector<float> texCoords_temp;
        int count_aux = 0;

        string model_path = string("../models/") + model_file;
        ifstream file(model_path);
        if (!file.is_open()){
            cerr << "[ERRO] Erro ao abrir ficheiro: " << model_file << endl;
            continue;
        }

        string line;
        getline(file, line);
        int num = 0;
        try {
            num = stoi(line);
        } catch (exception) {
            cerr << "[ERRO] Número de vértices inválido no ficheiro: " << model_file << endl;
            continue;
        }

        // Ler vértices
        for (int i = 0; i < num; i++) {
            getline(file,line);
            if (line.empty()) continue;

            istringstream iss(line);
            float x, y, z;
            if (!(iss >> x >> y >> z)) {
                cerr << "[ERRO] Erro ao ler vértice: " << line << endl;
                continue;
            }
            vertices_temp.push_back(x);
            vertices_temp.push_back(y);
            vertices_temp.push_back(z);
            count_aux += 1;
        }

        int normals_count = 0;
        // Ler normais
        for (int i = 0; i < num; i++) {
            getline(file,line);
            if (line.empty()) continue;

            istringstream iss(line);
            float x, y, z;
            if (!(iss >> x >> y >> z)) {
                cerr << "[ERRO] Erro ao ler normal: " << line << endl;
                continue;
            }
            normals_temp.push_back(x);
            normals_temp.push_back(y);
            normals_temp.push_back(z);
            normals_count += 1;
        }

        int texCoords_count = 0;
        // Ler coordenadas de textura
        for (int i = 0; i < num; i++) {
            getline(file,line);
            if (line.empty()) continue;

            istringstream iss(line);
            float u, v;
            if (!(iss >> u >> v)) {
                cerr << "[ERRO] Erro ao ler coordenadas de textura: " << line << endl;
                continue;
            }
            texCoords_temp.push_back(u);
            texCoords_temp.push_back(v);
            texCoords_count += 1;
        }

        file.close();

        // Validar consistência antes de adicionar
        if (count_aux != normals_count || count_aux != texCoords_count) {
            cerr << "[ERRO] Desalinhamento de dados em " << model_file << ": "
                 << count_aux << " vértices, " << normals_count << " normais, " 
                 << texCoords_count << " texturas" << endl;
            continue;
        }

        // Adicionar aos vetores globais apenas se tudo estiver correto
        vertices_aux.insert(vertices_aux.end(), vertices_temp.begin(), vertices_temp.end());
        normals_aux.insert(normals_aux.end(), normals_temp.begin(), normals_temp.end());
        texCoords_aux.insert(texCoords_aux.end(), texCoords_temp.begin(), texCoords_temp.end());
        g.addVerticeCount(count_aux);

    }

    if (vertices_aux.empty() || normals_aux.empty() || texCoords_aux.empty()) {
        cerr << "[ERRO] Nenhum vértice, normal ou coordenada de textura foi carregado!" << endl;
        return;
    } else if (vertices_aux.size() % 3 != 0 || normals_aux.size() % 3 != 0 || texCoords_aux.size() % 2 != 0) {
        cerr << "[ERRO] O número de vértices, normais ou coordenadas de textura não é múltiplo do esperado!" << endl;
        return;
    } else if (vertices_aux.size() / 3 != normals_aux.size() / 3 || vertices_aux.size() / 3 != texCoords_aux.size() / 2) {
        cerr << "[ERRO] O número de vértices, normais e coordenadas de textura não corresponde!" << endl;
        return;
    }

    GLuint* buffers = g.getBuffers();

    glGenBuffers(3, buffers);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,vertices_aux.size()*sizeof(float),&vertices_aux[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_aux.size() * sizeof(float), &(normals_aux[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, texCoords_aux.size() * sizeof(float), &(texCoords_aux[0]), GL_STATIC_DRAW);

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

void Data::initLights() {

    if (lights.empty()) return;
    else if (lights.size() > 8) {
        cerr << "[Aviso] Número de luzes excede o máximo (8)." << endl;
        exit(1);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_RESCALE_NORMAL);//Nota dos profs

    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

    // Propriedades por defeito das luzes
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    for (int i=0; i<lights.size(); i++) {
        GLenum light = static_cast<GLenum>(GL_LIGHT0 + i);
        glEnable(light);
        
        // Configurar propriedades de cor da luz
        glLightfv(light, GL_DIFFUSE, light_diffuse);
        glLightfv(light, GL_SPECULAR, light_specular);
        glLightfv(light, GL_AMBIENT, light_ambient);
    }

}

void Data::executeLights() {

    if (lights.empty()) return;

    int i = 0;
    for (Light* l : this->lights) {
        GLenum light = static_cast<GLenum>(GL_LIGHT0 + i);
     
        if (Point* p = dynamic_cast<Point*>(l)) {
            GLfloat position[] = { p->getPosX(), p->getPosY(), p->getPosZ(), 1.0f };
            glLightfv(light, GL_POSITION, position);
        } else if (Directional* d = dynamic_cast<Directional*>(l)) {
            GLfloat direction[] = { d->getDirX(), d->getDirY(), d->getDirZ(), 0.0f };
            normalize(direction);
            glLightfv(light, GL_POSITION, direction);
        } else if (Spotlight* s = dynamic_cast<Spotlight*>(l)) {
            GLfloat position[] = { s->getPosX(), s->getPosY(), s->getPosZ(), 1.0f };
            GLfloat direction[] = { s->getDirX(), s->getDirY(), s->getDirZ() };
            normalize(direction); 
            glLightfv(light, GL_POSITION, position);
            glLightfv(light, GL_SPOT_DIRECTION, direction);
            glLightf(light, GL_SPOT_CUTOFF, s->getCutoff());
            glLightf(light, GL_SPOT_EXPONENT, 0.0f); // Exponente de atenuação da luz
        } else {
            cerr << "[ERRO] Tipo de luz desconhecido!" << endl;
        }
        i++;
    }
}

void Data::setRenderCurve(bool flag) { renderCurve = flag; }

bool Data::getRenderCurve() { return renderCurve; }
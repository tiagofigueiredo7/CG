#include "engine/engine.hpp"

// Variáveis globais -----------Talvez guardar de forma melhor????? Tipo num ficheiro de configuração ou algo assim
float posX, posY, posZ;        // Camera position
float lookX, lookY, lookZ;     // Camera lookAt
float upX, upY, upZ;           // Camera up vector
float fov, nearPlane, farPlane;
int width, height;
vector<char *> model_files; // Para guardar vários modelos se necessário

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void createModel(char* model_file) {

    vector<float> vertices;

    ifstream file(model_file);
    if (!file.is_open()){
        cerr << "Erro ao abrir ficheiro" << model_file << endl;
        return;
    }

    string line;
    while(getline(file,line)){
        if (line.empty()) continue;

        istringstream iss(line);
        float x, y, z;
        if (!(iss >> x >> y >> z)) {
            cerr << "Erro ao ler vértice: " << line << endl;
            continue;
        }
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    //Terminar de criar o modelo
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, 
		      lookX, lookY, lookZ,
			  upX, upY, upZ);
    
    for (char* model_file : model_files) {
        createModel(model_file);
    }

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void processKeys(unsigned char key, int x, int y){

}


void processSpecialKeys(int key_code, int x, int y){

}

void processXML(char* file){
    // Valores padrão
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    fov = 60.0f;
    nearPlane = 1.0f;
    farPlane = 1000.0f;
    
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
        width = window->IntAttribute("width");
        height = window->IntAttribute("height");
    }
    
    // Ler camara
    XMLElement* camera = world->FirstChildElement("camera");
    if (camera) {
        
        // Position
        XMLElement* position = camera->FirstChildElement("position");
        if (position) {
            posX = position->FloatAttribute("x");
            posY = position->FloatAttribute("y");
            posZ = position->FloatAttribute("z");
        }
        
        // LookAt
        XMLElement* lookAt = camera->FirstChildElement("lookAt");
        if (lookAt) {
            lookX = lookAt->FloatAttribute("x");
            lookY = lookAt->FloatAttribute("y");
            lookZ = lookAt->FloatAttribute("z");
        }
        
        // Up (valores padrão se não existir)
        XMLElement* up = camera->FirstChildElement("up");
        if (up) {
            upX = up->FloatAttribute("x", 0.0f);
            upY = up->FloatAttribute("y", 1.0f);
            upZ = up->FloatAttribute("z", 0.0f);
        }
        
        // Projection
        XMLElement* projection = camera->FirstChildElement("projection");
        if (projection) {
            fov = projection->FloatAttribute("fov", 60.0f);
            nearPlane = projection->FloatAttribute("near", 1.0f);
            farPlane = projection->FloatAttribute("far", 1000.0f);
        }
    }
    
    // Ler group e models
    XMLElement* group = world->FirstChildElement("group");

    if (group){
        // Ler modelos
        XMLElement* models = group->FirstChildElement("models");
        if (models) {
            XMLElement* model;
            while((model = models->NextSiblingElement("model")) != nullptr) {
                const char* file = model->Attribute("file");
                if (file) {
                    model_files.push_back(strdup(file));
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "ERRO: Parâmetros insuficientes.";
        return 1; 
    }

    processXML(argv[1]);

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG-TP");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
    // put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);


    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
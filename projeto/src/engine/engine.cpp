#include "engine/engine.hpp"

// Variável global para armazenar os dados lidos do XML
Data store = Data();

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
	gluPerspective(store.getFov(), ratio, store.getNearPlane(), store.getFarPlane());

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void createModel(char* model_file) {

    vector<float> vertices;
    
    string model_path = string("../models/") + model_file;
    ifstream file(model_path);
    if (!file.is_open()){
        cerr << "[ERRO] Erro ao abrir ficheiro: " << model_file << endl;
        return;
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
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < vertices.size(); i += 3) {
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
        }
    glEnd();
}

void renderGroup(Group& g){
	glPushMatrix(); 

	for(Transformation* t : g.getTransformations()){
		if (Translate* tr = dynamic_cast<Translate*>(t)){
			glTranslatef(tr->getX(), tr->getY(), tr->getZ());
		}
		else if (Rotate* r = dynamic_cast<Rotate*>(t)){
			glRotatef(r->getAngle(), r->getX(), r->getY(), r->getZ());
		}
		else if (Scale* s = dynamic_cast<Scale*>(t)){
			glScalef(s->getX(), s->getY(), s->getZ());
		}
		else {
			cerr << "[ERRO] Transformação desconhecida!" << endl;
		}
	}

	for (char* mf : g.getModelFiles()){
		createModel(mf);
	}

	for (Group* gp : g.getSubGroups()){
		renderGroup(*gp);
	}

	glPopMatrix();

}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(store.getPosX(), store.getPosY(), store.getPosZ(), 
		      store.getLookX(), store.getLookY(), store.getLookZ(),
			  store.getUpX(), store.getUpY(), store.getUpZ());

    // Axis lines
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1000.0f, 0.0f, 0.0f);
		glVertex3f( 1000.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1000.0f, 0.0f);
		glVertex3f(0.0f, 1000.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -1000.0f);
		glVertex3f(0.0f, 0.0f, 1000.0f);
	glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 1.0f, 1.0f); // cor branca
	
	Group main_group = *store.getGroup();
    renderGroup(main_group);

	// End of frame
	glutSwapBuffers();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "[ERRO] Parâmetros insuficientes.";
        return 1; 
    }

    store.parseXML(argv[1]);

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(store.getWidth(), store.getHeight());
	glutCreateWindow("CG-TP");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
	
    // enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
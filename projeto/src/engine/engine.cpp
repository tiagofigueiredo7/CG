#include "engine/engine.hpp"

// Variável global para armazenar os dados lidos do XML
Data* store = new Data();

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
	gluPerspective(store->getFov(), ratio, store->getNearPlane(), store->getFarPlane());

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void createModel(int init, int count, GLuint* buffer){
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glVertexPointer(3,GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, init, count);
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
		else if (Curve* c = dynamic_cast<Curve*>(t)){
			//c->renderCatmullRomCurve();
			float elapsedSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			float time = c->getTime(), gt = fmod(elapsedSeconds,time) / time;		
			float pos[3], deriv[3];
			c->getGlobalCatmullRomPoint(gt, pos, deriv);
			glTranslatef(pos[0], pos[1], pos[2]);
			if (c -> getAlign()){
				float up[3] = {0,1,0};
				float x[3] = {deriv[0], deriv[1], deriv[2]}; normalize(x);
				float z[3]; cross(x, up, z); normalize(z); 
				float y[3]; cross(z, x, y); normalize(y);
				float m[16]; buildRotMatrix(x, y, z, m);
				glMultMatrixf(m);
			}
		}
		else if (TimedFullRotate* tfr = dynamic_cast<TimedFullRotate*>(t)){
			float elapsedSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;// obter tempo em segundos
			//se elapsedSeconds fosse int, iria acontecer uma rotação de 360/time graus por segundo, iria parecer que timha 1 fps
			float graus_sec = 360.0f / tfr->getTime();// graus por segundo
			float angle = fmod(elapsedSeconds * graus_sec, 360.0f);//tirar os graus em excesso
			glRotatef(angle, tfr->getX(), tfr->getY(), tfr->getZ());
		}
		else {
			cerr << "[ERRO] Transformação desconhecida!" << endl;
		}
	}

	int acumulador = 0;
	GLuint* buffer = g.getBuffer();
	if (buffer[0]) {
		for (int count : g.getVerticesCount()){
			createModel(acumulador,count,buffer);
			acumulador += count;
		}
	} 

	for (Group* gp : g.getSubGroups()){
		renderGroup(*gp);
	}

	glPopMatrix();

}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(store->getCamera())) {
		fpc->update_camera_LookAt();
	}

	// set the camera
	glLoadIdentity();
	Camera* cam = store->getCamera();
	gluLookAt(cam->getPosX(), cam->getPosY(), cam->getPosZ(),
		      cam->getLookX(), cam->getLookY(), cam->getLookZ(),
			  cam->getUpX(), cam->getUpY(), cam->getUpZ());

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
	
	Group* main_group = store->getGroup();
    if (main_group != nullptr) renderGroup(*main_group);

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	processKeys_aux(c, xx, yy, store);
}

void processKeysUp(unsigned char key, int xx, int yy) {
	processKeysUp_aux(key, xx, yy, store);
}

void processSpecialKeys(int key, int xx, int yy) {
	processSpecialKeys_aux(key, xx, yy, store);
}

void processMouseButtons(int button, int state, int xx, int yy) {
	processMouseButtons_aux(button, state, xx, yy, store);
}

void processMouseMotion(int xx, int yy) {
	processMouseMotion_aux(xx, yy, store);
}

void update_camera(int value) {
	Camera* cam = store->getCamera();
	if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(cam)) {
		fpc->update_camera_Pos();
		glutPostRedisplay();
	}

	glutTimerFunc(16, update_camera, 0);
}

int main(int argc, char** argv) {
    if (checkInputEngine(argc, argv[1]) == false) {
		return 1;
	}

	store->parse_Window_Information(argv[1]);

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(store->getWidth(), store->getHeight());
	glutCreateWindow("CG-TP");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);// Redesenha a cena quando o sistema estiver sem nada para fazer, pode se mudar o rendersence para uma função que chame  glutPostRedisplay() 
									//, onde a mesma manda um pedido para o Glut redesenhar a cena.
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(processKeysUp);
	glutSpecialFunc(processSpecialKeys);

	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);				

	// Glew
	glEnableClientState(GL_VERTEX_ARRAY);

	// init GLEW
#ifndef __APPLE__
	glewInit();
#endif

	store->parseXML(argv[1]);


    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	glutTimerFunc(16, update_camera, 0);  // ~60 FPS

    // enter GLUT's main cycle
	glutMainLoop();

	return 0;
}
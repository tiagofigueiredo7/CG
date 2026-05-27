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

void renderScene(void) {

	// Update FPS
	store->updateFPS();
	glutSetWindowTitle(store->getWindowTitle().c_str());

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Group* main_group = store->getGroup();
	Camera* cam = store->getCamera();

	// Atualizar posições world-space dos players sem a transformação da câmara.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if (main_group != nullptr) main_group->updateTargetsWorldPositions();
	glPopMatrix();

	if (store->getTargets().size() > 0) {

		if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {
			oc->update_cartesian_coordinates();
		}

	}

	// set the camera
	glLoadIdentity();
	gluLookAt(cam->getPosX(), cam->getPosY(), cam->getPosZ(),
		      cam->getLookX(), cam->getLookY(), cam->getLookZ(),
			  cam->getUpX(), cam->getUpY(), cam->getUpZ());

	store->executeLights();
	store->updateFrustum();
	

    // Axis lines
	// Desenha os eixos sem a iluminação
	GLboolean lightingWasEnabled = glIsEnabled(GL_LIGHTING);
	if (lightingWasEnabled) glDisable(GL_LIGHTING);

	if (store->getRenderExtraLines()) {

		glColor3f(1.0f, 0.0f, 0.0f);
		store->drawFrustum();

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

	}

	if (lightingWasEnabled) glEnable(GL_LIGHTING);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Nas fases anteriores estava  GL_LINE
    glColor3f(1.0f, 1.0f, 1.0f); // cor branca
	
    if (main_group != nullptr) main_group->renderGroup(store->getRenderExtraLines(), store->getFrustum());

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	if (c == 27) exit(0);
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
		fpc->update_camera_LookAt();
	}
	glutPostRedisplay();

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
	glutCreateWindow("GG-TP: Camera Normal");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);// Redesenha a cena quando o sistema estiver sem nada para fazer, pode se mudar o rendersence para uma função que chame  glutPostRedisplay() 
									//, onde a mesma manda um pedido para o Glut redesenhar a cena.
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(processKeysUp);
	glutSpecialFunc(processSpecialKeys);

	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);				;

	// init GLEW
	#ifndef __APPLE__
		glewInit();
	#endif

	ilInit();

	store->parseXML(argv[1]);

    //  OpenGL settings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	store->initLights();


	glutTimerFunc(16, update_camera, 0);  // ~60 FPS

    // enter GLUT's main cycle
	glutMainLoop();

	return 0;
}
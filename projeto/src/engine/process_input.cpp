#include "engine/process_input.hpp"

void processKeys_aux(unsigned char c, int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();

	if (c == '0' && (dynamic_cast<OrbitalCamera*>(cam) != nullptr || dynamic_cast<FirstPersonCamera*>(cam) != nullptr)) {
		Camera* new_cam = new Camera(store->getCamera());
		glutSetWindowTitle("GG-TP: Camera Normal");
		store->setCamera(new_cam);
	}
	else if (c == '1' && (dynamic_cast<OrbitalCamera*>(cam) == nullptr)) {
		OrbitalCamera* oc = new OrbitalCamera(cam, store->getPlayers().size());
		if (!store->getPlayers().empty()) {
			oc->incrementTargetIndex();
			oc->setTarget(store->getPlayerByIndex(oc->getTargetIndex()));
		}
		char title[100];
		snprintf(title, sizeof(title), "GG-TP: Camera Orbital - Target: %s", oc->getTarget() ? oc->getTarget()->getPlayerName().c_str() : "None");
		glutSetWindowTitle(title);
		store->setCamera(oc);
	}
	else if (c == '2' && (dynamic_cast<FirstPersonCamera*>(cam) == nullptr)) {
		FirstPersonCamera* fpc = new FirstPersonCamera(cam);
		glutSetWindowTitle("GG-TP: Camera de Primeira Pessoa");
		store->setCamera(fpc);
	}
	else if (c == '3' && (dynamic_cast<ThirdPersonCamera*>(cam) == nullptr)) {
		ThirdPersonCamera* tpc = new ThirdPersonCamera(cam, store->getPlayers().size());
		if (!store->getPlayers().empty()) {
			tpc->incrementTargetIndex();
			tpc->setTarget(store->getPlayerByIndex(tpc->getTargetIndex()));
		}
		char title[100];
		snprintf(title, sizeof(title), "GG-TP: Camera de Terceira Pessoa - Target: %s", tpc->getTarget() ? tpc->getTarget()->getPlayerName().c_str() : "None");
		glutSetWindowTitle(title);
		store->setCamera(tpc);
	}
	else if (c == 'r' || c == 'R') {//Render trajetoria da curva + eixos
		store->setRenderExtraLines(true);
	}
	else if (c == 'h' || c == 'H') {//Esconder trajetoria da curva + eixos
		store->setRenderExtraLines(false);
	}
	else if (c == 't' || c == 'T') { // Mudar target da OrbitalCamera
		if (store->getPlayers().size() == 0) return;
		else if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {
			oc->incrementTargetIndex();
			oc->setTarget(store->getPlayerByIndex(oc->getTargetIndex()));
			char title[100];
			snprintf(title, sizeof(title), "GG-TP: Camera Orbital - Target: %s", oc->getTarget() ? oc->getTarget()->getPlayerName().c_str() : "None");
			glutSetWindowTitle(title);
		}
		else if (ThirdPersonCamera* tpc = dynamic_cast<ThirdPersonCamera*>(cam)) {
			tpc->incrementTargetIndex();
			tpc->setTarget(store->getPlayerByIndex(tpc->getTargetIndex()));
			char title[100];
			snprintf(title, sizeof(title), "GG-TP: Camera de Terceira Pessoa - Target: %s", tpc->getTarget() ? tpc->getTarget()->getPlayerName().c_str() : "None");
			glutSetWindowTitle(title);
		}
	}
	else if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(cam)) {
		processKeys_Fpc_aux(c, xx, yy, fpc);
	} 
	else if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {
		processKeys_Orb_aux(c, xx, yy, oc);
	}
	else if (ThirdPersonCamera* tpc = dynamic_cast<ThirdPersonCamera*>(cam)) {
		processKeys_Tpc_aux(c,xx,yy, tpc);
	}
}

void processKeys_Tpc_aux(unsigned char c, int xx, int yy, ThirdPersonCamera* tpc) {

	if (c == 'Z' || c == 'z') tpc->setDistance(tpc->getDistance() - 0.5f);
	else if (c == 'X' || c == 'x') tpc->setDistance(tpc->getDistance() + 0.5f);
	else if (c == 'C' || c == 'c') tpc->setHeight(tpc->getHeight() - 0.5f);
	else if (c == 'V' || c == 'v') tpc->setHeight(tpc->getHeight() + 0.5f);
	else if (c == 'B' || c == 'b') {// Reset da distância, altura e lookHeight
		tpc->setDistance(6.0f);
		tpc->setHeight(2.5f);
		tpc->setLookHeight(1.0f);
	}

}

void processKeys_Orb_aux(unsigned char c, int xx, int yy, OrbitalCamera* oc) {
	if (c == '+') oc->update_zoom_speed(0.1f);
	if (c == '-') {
		if (oc->get_zoom_speed() <= 0.1f) {
			oc->set_zoom_speed(0.1f);
		} else {
			oc->update_zoom_speed(-0.1f);
		}
	}
}

void processKeys_Fpc_aux(unsigned char c, int xx, int yy, FirstPersonCamera* fpc) {
	if (c == 'w' || c == 'W') fpc->set_keyW(true);
	else if (c == 'a' || c == 'A') fpc->set_keyA(true);
	else if (c == 's' || c == 'S') fpc->set_keyS(true);
	else if (c == 'd' || c == 'D') fpc->set_keyD(true);
	else if (c == ' ') fpc->setPosY(fpc->getPosY() + fpc->get_move_speed());
	else if (c == '\t') fpc->setPosY(fpc->getPosY() - fpc->get_move_speed());
	else if (c == '+') fpc->update_move_speed(0.1f);
	else if (c == '-') {
		if (fpc->get_move_speed() <= 0.1f ) {
			fpc->set_move_speed(0.1f);
		} else {
			fpc->update_move_speed(-0.1f);
		}
	}
}


void processKeysUp_aux(unsigned char key, int xx, int yy, Data* store) {
	
	if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(store->getCamera())) {
		if (key == 'w' || key == 'W') fpc->set_keyW(false);
		if (key == 'a' || key == 'A') fpc->set_keyA(false);
		if (key == 's' || key == 'S') fpc->set_keyS(false);
		if (key == 'd' || key == 'D') fpc->set_keyD(false);
	}
}

void processSpecialKeys_aux(int key, int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();
	if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {

		switch (key) {

		case GLUT_KEY_RIGHT:
			oc->update_alpha(-0.1f); break;

		case GLUT_KEY_LEFT:
			oc->update_alpha(0.1f); break;

		case GLUT_KEY_UP:
			oc->update_beta(0.1f);
			if (oc->get_beta() > 1.5f)
				oc->set_beta(1.5f);
			break;

		case GLUT_KEY_DOWN:
			oc->update_beta(-0.1f);
			if (oc->get_beta() < -1.5f)
				oc->set_beta(-1.5f);
			break;

		case GLUT_KEY_PAGE_DOWN: 
			oc->update_radius(-oc->get_zoom_speed());
			if (oc->get_radius() < 0.1f)
				oc->set_radius(0.1f);
			break;

		case GLUT_KEY_PAGE_UP: 
			oc->update_radius(oc->get_zoom_speed());
			break;
		}
		oc->update_cartesian_coordinates();
		glutPostRedisplay();

	}

}

void processMouseButtons_aux(int button, int state, int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();
	if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(cam)) {
	
		if (state == GLUT_DOWN)  {
			fpc->set_startX(xx);
			fpc->set_startY(yy);
			fpc->set_tracking(1);
		}
		else if (state == GLUT_UP) {
			fpc->set_tracking(0);
		}
	}
}

void processMouseMotion_aux(int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();
	if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(cam)) {
		if (!fpc->get_tracking())
			return;

		// Cálculo do ângulo yaw(alpha) a partir do movimento horizontal do mouse
		int deltaX = xx - fpc->get_startX();
		fpc->set_alpha(fpc->get_alpha() + deltaX * 0.5f);

		// Cálculo do ângulo pitch(beta) a partir do movimento vertical do mouse
		int deltaY = yy - fpc->get_startY();
		float beta = fpc->get_beta() - deltaY * 0.3f;
		if (beta > 89.0f) beta = 89.0f;
		if (beta < -89.0f) beta = -89.0f;
		fpc->set_beta(beta);
		
		fpc->set_startX(xx);
		fpc->set_startY(yy);
		
	}
}

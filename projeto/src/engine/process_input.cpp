#include "engine/process_input.hpp"

void processKeys_aux(unsigned char c, int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();

	if (c == '0' && (dynamic_cast<OrbitalCamera*>(cam) != nullptr || dynamic_cast<FirstPersonCamera*>(cam) != nullptr)) {
		Camera* new_cam = new Camera(store->getCamera());
		store->setCamera(new_cam);
	}
	else if (c == '1' && (dynamic_cast<OrbitalCamera*>(cam) == nullptr)) {
		OrbitalCamera* oc = new OrbitalCamera(cam);
		store->setCamera(oc);
	}
	else if (c == '2' && (dynamic_cast<FirstPersonCamera*>(cam) == nullptr)) {
		FirstPersonCamera* fpc = new FirstPersonCamera(cam);
		store->setCamera(fpc);
	} 
	else if (FirstPersonCamera* fpc = dynamic_cast<FirstPersonCamera*>(cam)) {
		processKeys_Fpc_aux(c, xx, yy, fpc);
	} 
	else if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {
		processKeys_Orb_aux(c, xx, yy, oc);
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

		// Only control horizontal rotation (alpha) with mouse movement
		int deltaX = xx - fpc->get_startX();
		fpc->set_alpha(fpc->get_alpha() + deltaX * 0.5f);  // Scale mouse movement for smoother control
		
		fpc->set_startX(xx);
		fpc->set_startY(yy);
		
	}
}

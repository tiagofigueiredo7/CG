#include "engine/process_input.hpp"


void processKeys_aux(unsigned char c, int xx, int yy, Data* store) {

	Camera* cam = store->getCamera();

	if (c == '0' && (dynamic_cast<OrbitalCamera*>(cam) != nullptr || dynamic_cast<FirstPersonCamera*>(cam) != nullptr)) {
		Camera* new_cam = new Camera(store->getCamera());
		store->setCamera(new_cam);
	}
	else if (c == '1' && (dynamic_cast<OrbitalCamera*>(cam) == nullptr)) {
		OrbitalCamera* oc = new OrbitalCamera(cam, store->getTargets().size());
		if (!store->getTargets().empty()) {
			oc->incrementTargetIndex();
			oc->setTarget(store->getTargetByIndex(oc->getTargetIndex()));
		}
		store->setCamera(oc);
	}
	else if (c == '2' && (dynamic_cast<FirstPersonCamera*>(cam) == nullptr)) {
		FirstPersonCamera* fpc = new FirstPersonCamera(cam);
		store->setCamera(fpc);
	}
	else if (c == 'r' || c == 'R') {//Renderizar ou esconder trajetoria da curva + eixos
		store->setRenderExtraLines(!store->getRenderExtraLines());
	}
	else if (c == 'f' || c == 'F') {//Renderizar ou esconder frustum
		store->setRenderFrustum(!store->getRenderFrustum());
	}
	else if (c == 't' || c == 'T') { // Mudar target da OrbitalCamera
		if (store->getTargets().size() == 0) return;
		else if (OrbitalCamera* oc = dynamic_cast<OrbitalCamera*>(cam)) {
			oc->incrementTargetIndex();
			oc->setTarget(store->getTargetByIndex(oc->getTargetIndex()));
		}
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

	if (state == GLUT_DOWN) {
		if (store->getTargets().size() == 0) return;
		bool valid;
		Point3D worldCoords = picking(xx, yy, &valid);
		if (valid) {
			verificarSelecao(worldCoords, store);
		} else return;

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

Point3D picking(int mouseX, int mouseY, bool* valid) {
	
	int viewport[4]; 
	glGetIntegerv(GL_VIEWPORT, viewport);
	float winX = (float)mouseX;
	float winY = (float)(viewport[3] - mouseY - 1); // flip Y
	float winZ;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	if (winZ == 1.0f) {
		*valid = false;
		return {0.0f, 0.0f, 0.0f}; // Retorna um ponto invalido se o clique for no fundo
	}

	float x = (2.0f * winX) / viewport[2] - 1.0f;
	float y = (2.0f * winY) / viewport[3] - 1.0f;
	float z = 2.0f * winZ - 1.0f;

	float vector[4] = {x, y, z, 1.0f};
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	float projection[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	// Compor matriz proj * modelview
	float projModelview[16];
	multMatrix(projection, modelview, projModelview);

	// Inverter a matriz composta
	float invProjModelview[16];
	if (!invertMatrix(projModelview, invProjModelview)) {
		*valid = false;
		return {0.0f, 0.0f, 0.0f}; // Matriz singular, nao inversivel
	}

	// Transformar ponto de NDC para coordenadas do mundo
	float worldCoords[4];
	multiMatrixVector_ColumnMajor(invProjModelview, vector, worldCoords);

	// Dividir por w para perspetiva
	worldCoords[0] /= worldCoords[3];
	worldCoords[1] /= worldCoords[3];
	worldCoords[2] /= worldCoords[3];

	*valid = true;
	return {worldCoords[0], worldCoords[1], worldCoords[2]};
}

void verificarSelecao(Point3D clickPos, Data* store) {
	if (store->getTargets().size() == 0) return;
	

	Group* selectedTarget = nullptr;
	float minDistance = numeric_limits<float>::max();

	int selectedIndex = -1;
	int groupIndex = 0;

	for (Group* target : store->getTargets()) {
		if (target->getModelCenters_world().size() == 0) {
			groupIndex++;
			continue;
		}
		
		for (size_t i = 0; i < target->getModelCenters_world().size(); ++i) {
			Point3D center = target->getModelCenters_world()[i];
			float raio = target->getRaiosEsferas_world()[i];
			float distance = sqrt(pow(clickPos.x - center.x, 2) + pow(clickPos.y - center.y, 2) + pow(clickPos.z - center.z, 2));
			
			if (raio > 0 && distance <= raio && distance < minDistance) {
				minDistance = distance;
				selectedTarget = target;
				selectedIndex = groupIndex;
			}
		}
		groupIndex++;
	}

	if (!selectedTarget || selectedIndex < 0) {
		return;
	}

	Camera* cam = store->getCamera();
	OrbitalCamera* oc;
	if (dynamic_cast<OrbitalCamera*>(cam) == nullptr) {
		oc = new OrbitalCamera(cam, store->getTargets().size());
	} else {
		oc = dynamic_cast<OrbitalCamera*>(cam);
	}

	oc->setIndex(selectedIndex);
	oc->setTarget(store->getTargetByIndex(selectedIndex));
	store->setCamera(oc);
}

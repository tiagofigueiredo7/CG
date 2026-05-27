#include "engine/structs/Group.hpp"

// Construtor
Group::Group() {
    this->buffers = (GLuint*)malloc(sizeof(GLuint) * 3);
    this->buffers[0] = 0;
	this->buffers[1] = 0;
	this->buffers[2] = 0;
    this->transformations = vector<Transformation*>();
    this->subgroups = vector<Group*>();
    this->vertices_count = vector<int>();
	this->materials = vector<Material*>();
	this->texturesIDs = vector<GLuint*>();
	this->raios_Esferas = vector<float>();
	this->raios_Esferas_world = vector<float>();
	this->modelCenters = vector<Point3D>();
	this->modelCenters_world = vector<Point3D>();

	this->isTarget = false;
	this->targetName = "";
	this->globalPosition = {0.0f, 0.0f, 0.0f};
}

// Destrutor
Group::~Group() {
    for (Transformation* t : this->getTransformations()){
        delete t;
    }

    for (Group* g: this->getSubGroups()){
        delete g;
    }

	for (Material* m : this->getMaterials()) {
		delete m;
	}

	for (GLuint* g : this->getTexturesIDs()) {
		free(g);
	}

	// Liberar VBO da GPU antes de liberar o ponteiro
    if (this->buffers[0] != 0 && this->buffers[1] != 0 && this->buffers[2] != 0) {
        glDeleteBuffers(3, this->buffers);
    }


    free(this->buffers);

    
}

const vector<Transformation*>& Group::getTransformations() { return transformations; }

const vector<Group* >& Group::getSubGroups() { return subgroups; }

const vector<Material*>& Group::getMaterials() { return materials; }

GLuint* Group::getBuffers(){ return buffers; }

const vector<int>& Group::getVerticesCount() { return vertices_count; }

const vector<GLuint*>& Group::getTexturesIDs() { return texturesIDs; }

void Group::addTransformation(Transformation* transf){ transformations.push_back(transf); }

void Group::addSubGroup(Group* subgroup) { subgroups.push_back(subgroup); }

void Group::addVerticeCount(int count) { vertices_count.push_back(count); }

void Group::addMaterial(Material* material) { materials.push_back(material); }

void Group::addTextureID(GLuint* id) { texturesIDs.push_back(id); }

void Group::addRaioEsfera_world(float raio) { this->raios_Esferas_world.push_back(raio); }

bool Group::getIsTarget() {
	return isTarget;
}

void Group::setIsTarget(bool isTarget) {
	this->isTarget = isTarget;
}

string Group::getTargetName() {
	return targetName;
}

void Group::setTargetName(string targetName) {
	this->targetName = targetName;
}

Point3D Group::getGlobalPosition() {
	return globalPosition;
}

void Group::setGlobalPosition(float x, float y, float z) {
	this->globalPosition = {x, y, z};
}

const vector<float>& Group::getRaiosEsferas() {
	return raios_Esferas;
}

const vector<float>& Group::getRaiosEsferas_world() {
	return raios_Esferas_world;
}

const vector<Point3D>& Group::getModelCenters() {
	return modelCenters;
}

void Group::addRaioEsfera(float raio) {
	this->raios_Esferas.push_back(raio);
}

void Group::addModelCenter(Point3D c) {
	this->modelCenters.push_back(c);
}

void Group::addModelCenter_world(Point3D c) {
	this->modelCenters_world.push_back(c);
}

void Group::setRaiosEsferas_world(float raio, int index) {
	if (index >= 0 && index < raios_Esferas_world.size()) {
		this->raios_Esferas_world[index] = raio;
	}
}

const vector<Point3D>& Group::getModelCenters_world() {
	return modelCenters_world;
}

void Group::setModelCenters_world(Point3D p, int index) {
	if (index >= 0 && index < modelCenters_world.size()) {
		this->modelCenters_world[index] = p;
	}
}

// Renderização

void Group::renderGroup(bool renderExtraLines, Frustum* f) {
	glPushMatrix(); 

	for(Transformation* t : this->getTransformations()){
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
			if (renderExtraLines) c->renderCatmullRomCurve();
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
	GLuint* buffers = this->getBuffers();
	if (buffers[0] && buffers[1] && buffers[2]) {

		vector<Point3D> centers = this->getModelCenters();
		for (size_t i = 0; i < materials.size() && i < vertices_count.size() && i < texturesIDs.size() && i < raios_Esferas.size(); ++i) {
			Point3D worldcenter = this->getModelCenters_world()[i];
			float worldRadius = this->getRaiosEsferas_world()[i];
			if (!f->sphereInFrustum(worldcenter.x, worldcenter.y, worldcenter.z, worldRadius)) {
				acumulador += vertices_count[i];
				if (this->getIsTarget()) {
					//printf("%s\n", this->getPlayerName().c_str());
				}
				continue; // Pular este modelo se a esfera circunscrita não estiver no frustum
			}
			materials[i]->aplicarMaterial();
			createModel(acumulador, vertices_count[i], buffers, texturesIDs[i]);
			acumulador += vertices_count[i];
		}
	} 

	for (Group* gp : this->getSubGroups()){
		gp->renderGroup(renderExtraLines, f);
	}

	glPopMatrix();

}

void Group::createModel(int init, int count, GLuint* buffers, GLuint* textureID) {
    if (buffers == nullptr || count <= 0) {
        return;
    }

    bool hasTexture = (textureID != nullptr && *textureID != 0);
    int bufferCount = hasTexture ? 3 : 2;

    if (!glIsBuffer(buffers[0]) || !glIsBuffer(buffers[1]) || 
        (hasTexture && !glIsBuffer(buffers[2]))) {
        cerr << "[ERRO] Buffer(s) inválido(s)!" << endl;
        return;
    }
    
    GLboolean texture2DWasEnabled = glIsEnabled(GL_TEXTURE_2D);
    GLboolean textureArrayWasEnabled = glIsEnabled(GL_TEXTURE_COORD_ARRAY);

    if (hasTexture) {
        glBindTexture(GL_TEXTURE_2D, *textureID);
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
    } else {
        glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glNormalPointer(GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, init, count);

    if (hasTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    // Restaurar estado anterior
    if (!hasTexture && textureArrayWasEnabled) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    if (!texture2DWasEnabled) {
        glDisable(GL_TEXTURE_2D);
    }
}

void Group::updateTargetsWorldPositions() {

	glPushMatrix();

	for (Transformation* t : this->getTransformations()) {
		if (Translate* tr = dynamic_cast<Translate*>(t)) {
			glTranslatef(tr->getX(), tr->getY(), tr->getZ());
		}
		else if (Rotate* r = dynamic_cast<Rotate*>(t)) {
			glRotatef(r->getAngle(), r->getX(), r->getY(), r->getZ());
		}
		else if (Scale* s = dynamic_cast<Scale*>(t)) {
			glScalef(s->getX(), s->getY(), s->getZ());
		}
		else if (Curve* c = dynamic_cast<Curve*>(t)) {
			float elapsedSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			float time = c->getTime(), gt = fmod(elapsedSeconds, time) / time;
			float pos[3], deriv[3];
			c->getGlobalCatmullRomPoint(gt, pos, deriv);
			glTranslatef(pos[0], pos[1], pos[2]);
			if (c->getAlign()) {
				float up[3] = {0, 1, 0};
				float x[3] = {deriv[0], deriv[1], deriv[2]}; normalize(x);
				float z[3]; cross(x, up, z); normalize(z);
				float y[3]; cross(z, x, y); normalize(y);
				float m[16]; buildRotMatrix(x, y, z, m);
				glMultMatrixf(m);
			}
		}
		else if (TimedFullRotate* tfr = dynamic_cast<TimedFullRotate*>(t)) {
			float elapsedSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			float graus_sec = 360.0f / tfr->getTime();
			float angle = fmod(elapsedSeconds * graus_sec, 360.0f);
			glRotatef(angle, tfr->getX(), tfr->getY(), tfr->getZ());
		}
	}

	GLfloat modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	this->setGlobalPosition(modelview[12], modelview[13], modelview[14]);
	float sx = sqrtf(modelview[0] * modelview[0] + modelview[1] * modelview[1] + modelview[2] * modelview[2]);
	float sy = sqrtf(modelview[4] * modelview[4] + modelview[5] * modelview[5] + modelview[6] * modelview[6]);
	float sz = sqrtf(modelview[8] * modelview[8] + modelview[9] * modelview[9] + modelview[10] * modelview[10]);
	float scaleMax = fmaxf(sx, fmaxf(sy, sz));


	vector<Point3D> centers = this->getModelCenters();
	for (size_t i = 0; i < this->getMaterials().size() && i < this->getVerticesCount().size() && i < this->getTexturesIDs().size() && i < this->getRaiosEsferas().size(); ++i) {
		float centerX = this->getGlobalPosition().x;
		float centerY = this->getGlobalPosition().y;
		float centerZ = this->getGlobalPosition().z;
		if (i < centers.size()) {
			GLfloat modelview[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			float localCenter[4] = { centers[i].x, centers[i].y, centers[i].z, 1.0f };
			float worldCenter[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			multiMatrixVector_ColumnMajor(modelview, localCenter, worldCenter);
			centerX = worldCenter[0];
			centerY = worldCenter[1];
			centerZ = worldCenter[2];

			this->setModelCenters_world(Point3D{centerX, centerY, centerZ}, i);
			this->setRaiosEsferas_world(raios_Esferas[i] * scaleMax, i);


		}
		
	}

	for (Group* gp : this->getSubGroups()) {
		gp->updateTargetsWorldPositions();
	}

	glPopMatrix();
}

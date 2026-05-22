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

	this->isPlayer = false;
	this->playerName = "";
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

// Getters
vector<Transformation*> Group::getTransformations() { return transformations; }

vector<Group* >Group::getSubGroups(){ return subgroups; }

vector<Material*> Group::getMaterials() { return materials; }

GLuint* Group::getBuffers(){ return buffers; }

vector<int> Group::getVerticesCount() { return vertices_count; }

vector<GLuint*> Group::getTexturesIDs() { return texturesIDs; }

// Add
void Group::addTransformation(Transformation* transf){ transformations.push_back(transf); }

void Group::addSubGroup(Group* subgroup) { subgroups.push_back(subgroup); }

void Group::addVerticeCount(int count) { vertices_count.push_back(count); }

void Group::addMaterial(Material* material) { materials.push_back(material); }

void Group::addTextureID(GLuint* id) { texturesIDs.push_back(id); }

// Renderização

void Group::renderGroup(Data* data){
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
			if (data->getRenderExtraLines()) c->renderCatmullRomCurve();
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
		for (size_t i = 0; i < materials.size() && i < vertices_count.size() && i < texturesIDs.size(); ++i) {
			materials[i]->aplicarMaterial();
			if (texturesIDs[i] != nullptr && *texturesIDs[i] != 0) {
				createModel_wTexture(acumulador, vertices_count[i], buffers, texturesIDs[i]);
			} else {
				createModel(acumulador, vertices_count[i], buffers);
			}
			acumulador += vertices_count[i];
		}
	} 

	for (Group* gp : this->getSubGroups()){
		gp->renderGroup(data);
	}

	glPopMatrix();

}

void Group::createModel_wTexture(int init, int count, GLuint* buffers, GLuint* textureID){

	if (buffers == nullptr || textureID == nullptr || count <= 0) {
		return;
	}

	if (!glIsBuffer(buffers[0]) || !glIsBuffer(buffers[1]) || !glIsBuffer(buffers[2])) {
		cerr << "[ERRO] Buffer(s) inválido(s) ao desenhar modelo com textura!" << endl;
		return;
	}

	GLint vertexSize = 0;
	GLint normalSize = 0;
	GLint textureSize = 0;
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vertexSize);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &normalSize);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &textureSize);

	if (vertexSize < count * 3 * static_cast<GLint>(sizeof(float)) ||
		normalSize < count * 3 * static_cast<GLint>(sizeof(float)) ||
		textureSize < count * 2 * static_cast<GLint>(sizeof(float))) {
		cerr << "[ERRO] Buffer(s) demasiado pequeno(s) ao desenhar modelo com textura!" << endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Habilitar caso esteja desabilitado
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glNormalPointer(GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
	glTexCoordPointer(2,GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, init, count);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Group::createModel(int init, int count, GLuint* buffers){

	if (buffers == nullptr || count <= 0) {
		return;
	}

	if (!glIsBuffer(buffers[0]) || !glIsBuffer(buffers[1])) {
		cerr << "[ERRO] Buffer(s) inválido(s) ao desenhar modelo!" << endl;
		return;
	}

	GLint vertexSize = 0;
	GLint normalSize = 0;
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vertexSize);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &normalSize);

	if (vertexSize < count * 3 * static_cast<GLint>(sizeof(float)) ||
		normalSize < count * 3 * static_cast<GLint>(sizeof(float))) {
		cerr << "[ERRO] Buffer(s) demasiado pequeno(s) ao desenhar modelo!" << endl;
		return;
	}

	GLboolean texture2DWasEnabled = glIsEnabled(GL_TEXTURE_2D);
	GLboolean textureArrayWasEnabled = glIsEnabled(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glNormalPointer(GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, init, count);

	if (textureArrayWasEnabled) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	if (texture2DWasEnabled) {
		glEnable(GL_TEXTURE_2D);
	}
}

bool Group::getIsPlayer() {
	return isPlayer;
}

void Group::setIsPlayer(bool isPlayer) {
	this->isPlayer = isPlayer;
}

string Group::getPlayerName() {
	return playerName;
}

void Group::setPlayerName(string playerName) {
	this->playerName = playerName;
}

Pos Group::getGlobalPosition() {
	return globalPosition;
}

void Group::setGlobalPosition(float x, float y, float z) {
	this->globalPosition = {x, y, z};
}

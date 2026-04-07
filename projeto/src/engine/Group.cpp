#include "engine/Group.hpp"

// Construtor
Group::Group() {
    this->buffer = (GLuint*)malloc(sizeof(GLuint));
    this->buffer[0] = 0;
    this->transformations = vector<Transformation*>();
    this->subgroups = vector<Group*>();
    this->vertices_count = vector<int>();
}

// Destrutor
Group::~Group() {
    for (Transformation* t : this->getTransformations()){
        delete t;
    }

    for (Group* g: this->getSubGroups()){
        delete g;
    }

    // Liberar VBO da GPU antes de liberar o ponteiro
    if (this->buffer[0] != 0) {
        glDeleteBuffers(1, this->buffer);
    }

    free(this->buffer);

}

// Getters
vector<Transformation*> Group::getTransformations() { return transformations; }

vector<Group* >Group::getSubGroups(){ return subgroups; }

GLuint* Group::getBuffer(){ return buffer; }

vector<int> Group::getVerticesCount() { return vertices_count; }

// Add
void Group::addTransformation(Transformation* transf){ transformations.push_back(transf); }

void Group::addSubGroup(Group* subgroup) { subgroups.push_back(subgroup); }

void Group::addVerticeCount(int count) { vertices_count.push_back(count); }

// Renderização

void Group::renderGroup(){
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
	GLuint* buffer = this->getBuffer();
	if (buffer[0]) {
		for (int count : this->getVerticesCount()){
			createModel(acumulador,count,buffer);
			acumulador += count;
		}
	} 

	for (Group* gp : this->getSubGroups()){
		gp->renderGroup();
	}

	glPopMatrix();

}

void Group::createModel(int init, int count, GLuint* buffer){
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glVertexPointer(3,GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, init, count);
}

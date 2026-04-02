#include "utils/util.hpp"

namespace util {

	// Armazena os vértices gerados no ficheiro
	void storeVertices(const vector<float>& vertices, const string& file) {
		ofstream out("../models/" + file);
		if (!out.is_open()) {
			cerr << "[ERRO] Não foi possível abrir o ficheiro.";
			return;
		}
		for (size_t i = 0; i < vertices.size(); i += 3) {
			out << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n"; // um ponto (3 coordenadas) por linha
		}
		out.close();
	}

	bool checkInputEngine(const int parameters , const string scene){
		if (parameters != 2) {
			cerr << "[ERRO] Parâmetros inválidos para a cena " << scene << ".\n[USO] engine <scene file>\n";
			return false;
		} else if (scene.find(".xml") == string::npos) {
			cerr << "[ERRO] O ficheiro da cena deve ser um ficheiro XML.\n[USO] engine <scene file>\n";
			return false;
		}
		return true;
	}
	
	// Fazer a verificação do input do generator
	bool checkInputGenerator(const int parameters , const string figure){
		if (figure == "plane"){
			if(parameters != 5) {
				cerr << "[ERRO] Parâmetros inválidos para a figura plane.\n[USO] generator plane <length> <divisions> <dest file>\n";
				return false;
			}
		}
		else if (figure == "box"){
			if(parameters != 5) {
				cerr << "[ERRO] Parâmetros inválidos para a figura box.\n[USO] generator box <length> <divisions> <dest file>\n";
				return false;
			}
		}
		else if (figure == "sphere"){
			if(parameters != 6) {
				cerr << "[ERRO] Parâmetros inválidos para a figura sphere.\n[USO] generator sphere <radius> <slices> <stacks> <dest file>\n";
				return false;
			}
		}
		else if (figure == "cone"){
			if(parameters != 7) {
				cerr << "[ERRO] Parâmetros inválidos para a figura cone.\n[USO] generator cone <radius> <height> <slices> <stacks> <dest file>\n";
				return false;
			}
		}
		else if (figure == "torus"){
			if(parameters != 7) {
				cerr << "[ERRO] Parâmetros inválidos para a figura torus.\n[USO] generator torus <majorRadius> <minorRadius> <slices> <stacks> <dest file>\n";
				return false;
			}
		}
		else if(figure == "cylinder"){
			if(parameters != 6) {
				cerr << "[ERRO] Parâmetros inválidos para a figura cylinder.\n[USO] generator cylinder <radius> <height> <slices> <dest file>\n";
				return false;
			}
		}
		else if(figure == "mobiusStrip"){
			if(parameters != 6) {
				cerr << "[ERRO] Parâmetros inválidos para a figura mobius strip.\n[USO] generator mobiusStrip <radius> <width> <slices> <dest file>\n";
				return false;
			}
		}
		else if(figure == "noiseSphere"){
			if(parameters != 7) {
				cerr << "[ERRO] Parâmetros inválidos para a figura noise sphere.\n[USO] generator noiseSphere <radius> <slices> <stacks> <amplitude> <dest file>\n";
				return false;
			}
		}
		else if(figure == "patch"){
			if(parameters != 5) {
				cerr << "[ERRO] Parâmetros inválidos para a figura patch.\n[USO] generator patch <patch file> <tesselation> <dest file>\n";
				return false;
			}
		}
		else {
			cerr << "[ERRO] Figura não suportada.\n";
			return false;
		}
		return true;
	}

    // Adiciona coordenadas dos vértices de um trinânculo a um vetor
	void addTriangle(vector<float>& v, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
		v.push_back(x1);
		v.push_back(y1);
		v.push_back(z1);
		v.push_back(x2);
		v.push_back(y2);
		v.push_back(z2);
		v.push_back(x3);
		v.push_back(y3);
		v.push_back(z3);
	}

	// Multiplica matriz 4x4 por vetor
	void multMatrixVector(float *m, float *v, float *res) {

		for (int j = 0; j < 4; ++j) {
			res[j] = 0;
			for (int k = 0; k < 4; ++k) {
				res[j] += v[k] * m[j * 4 + k];
			}
		}

	}

	// Constrói matriz de rotação
	void buildRotMatrix(float *x, float *y, float *z, float *m) {
		m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
		m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
		m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}

	// Produto vetorial de dois vetores
	void cross(float *a, float *b, float *res) {
		res[0] = a[1]*b[2] - a[2]*b[1];
		res[1] = a[2]*b[0] - a[0]*b[2];
		res[2] = a[0]*b[1] - a[1]*b[0];
	}

	// Normaliza vetor
	void normalize(float *a) {
		float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
		a[0] = a[0]/l;
		a[1] = a[1]/l;
		a[2] = a[2]/l;
	}
}

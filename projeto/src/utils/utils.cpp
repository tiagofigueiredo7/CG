#include "utils/util.hpp"

namespace util {

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
		else if(figure == "kleinBottle"){
			if(parameters != 8) {
				cerr << "[ERRO] Parâmetros inválidos para a figura klein bottle.\n[USO] generator kleinBottle <slices> <stacks> <scale> <tubeRadius> <heightStretch> <dest file>\n";
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

	// Multiplica matriz 4x4 por vetor
	void multMatrixVector(float *m, float *v, float *res) {

		for (int j = 0; j < 4; ++j) {
			res[j] = 0;
			for (int k = 0; k < 4; ++k) {
				res[j] += v[k] * m[j * 4 + k];
			}
		}

	}

	void multiMatrixVector_ColumnMajor(float *m, float *v, float *res) {

		for (int j = 0; j < 4; ++j) {
			res[j] = 0;
			for (int k = 0; k < 4; ++k) {
				res[j] += m[j + k * 4] * v[k];
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

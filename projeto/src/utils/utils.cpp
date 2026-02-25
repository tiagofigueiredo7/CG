#include "utils/util.hpp"

namespace util {
	// Fazer a verificação do input do generator
	bool checkInput(const int parameters , const string figure){
		if (figure == "plane"){
			if(parameters != 5) {
				cerr << "[ERRO] Parâmetros inválidos para a figura plane.\n[USO] generator plane <size> <divisions> <dest file>\n";
				return false;
			}
		}
		else if (figure == "box"){
			if(parameters != 5) {
				cerr << "[ERRO] Parâmetros inválidos para a figura box.\n[USO] generator box <size> <divisions> <dest file>\n";
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
		else if(figure == "cilinder"){
			if(parameters != 6) {
				cerr << "[ERRO] Parâmetros inválidos para a figura cilinder.\n[USO] generator cilinder <radius> <height> <slices> <dest file>\n";
				return false;
			}
		}
		else {
			cerr << "[ERRO] Figura não suportada.";
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
}

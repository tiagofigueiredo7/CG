#include "utils/utils.hpp"

namespace utils {
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

	// Função auxiliar para extrair valor de atributo
	string getAttribute(const string& line, const string& attr) {
		size_t pos = line.find(attr + "=\"");
		if (pos == string::npos) return "";
		
		pos += attr.length() + 2; // pular attr="
		size_t end = line.find("\"", pos);
		return line.substr(pos, end - pos);
	}
}


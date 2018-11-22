#ifndef GRAFO
#define GRAFO

#include <string>

typedef struct NO {
	std::string id;
	std::string label;
	float size;
	int r;
	int g;
	int b;
	float x;
	float y;
	NO *prox;
};

typedef struct ARESTA {
	std::string id;
	std::string source;
	std::string target;
	float weight;
	ARESTA *prox;
};
#endif
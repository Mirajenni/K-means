#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GrafoXML.h"
#include "Grafo.h"
#include "K-means.h"
#include <vector>

using namespace std;

int main() {
	int K = 4;
	extern int tamanhoNO;
	extern int tamanhoARESTA;
	extern NO *no[10000];
	extern ARESTA *aresta[10000];
	if (lerXML() == 0)
		cout << "Falha ao ler Grafo!" << endl;
	cout << "Grafo lido com sucesso!" << endl;

	if (salvarXML() == 0)
		return 0;
	cout << "Arquivo 'Novo Grafo1' salvo!" << endl;
	cout << "qtd nos " << tamanhoNO << endl;
	cout << "qtd arestas " << tamanhoARESTA << endl;
	/*for (int i = 0; i < tamanhoARESTA; i++) {

		cout << "id " << aresta[i]->id << endl;
		//cout << "source " << aresta[i]->source << endl;
		//cout << "target  " << aresta[i]->target << endl;
		cout << "weight " << aresta[i]->weight << endl;

	}*/
	//Fazer o k-means do grafo
	std::vector<int> vetorm;
	vetorm = k_means(K, 10); //passa o K e numero de iterações
	cout << "k-means terminado!" << endl;
	system("pause");
	return 0;
}

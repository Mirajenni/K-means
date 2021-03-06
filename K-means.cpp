
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>
#include <vector>
#include <iostream>
#include <set>
#include "GrafoXML.h"
#include "Grafo.h"

extern NO *no[10000];
extern ARESTA *aresta[10000];

extern int tamanhoNO;
extern int tamanhoARESTA;

const int N = 7;
//valores globais
const int K = 2;

#define	VERTICE_MAX	10
const int INF = 0x3f3f3f3f;


int vertices[VERTICE_MAX] = { 1,2,3,4,5,6,7 };
//assumindo que a matriz de adjacência e shortestDistances sejam estáticas. Isso muda de grafo pra grafo. Possívelmente precisará fazer um floyd-warshall
//pra achar a matriz de shortestDistances


//usar matriz de adj para ler
int *matriz[VERTICE_MAX];

void matriz_peso(ARESTA *ar[], int *dado[]) {
std::string::size_type sz;

dado = new int *[tamanhoNO];
for (int i = 0; i<tamanhoNO; i++) {
dado[i] = new int[tamanhoNO];
}
//iniciar com -1 a matriz para quando não tiver match de vertices
for (int i = 0; i < tamanhoNO; i++) {
for (int j = 0; j < tamanhoNO; j++) {
dado[i][j] = -1;
}
}
if (ar != NULL) {
//Percorrer a lista de aresta e acrescentar na matriz
for (int i = 0; i < tamanhoARESTA; i++) {
if (ar[i]->source == ar[i]->target) {
dado[i][i] = 0;
}
else {
int s = std::stoi(ar[i]->source);
int t = std::stoi(ar[i]->target);
dado[s][t] = int(ar[i]->weight);
}
}
}
}


std::vector<int> k_means(int k, size_t number_of_iterations) {
ARESTA **ar;
int **dado;
//matriz_peso(ar, dado); //matriz de dado atualizada nesse procedimento
std::random_device rd;
std::vector<int> new_means(k);
std::mt19937 eng(rd());
std::uniform_int_distribution<> distr(1, N); // seeds de c++ pra gerar vértices randômicos de 0 até N-1
std::set<int> centroids; // ideia de armazenar todos os centróides em set's pra saber quem pertence a quem
// Pick centroids as random points from the dataset.
std::vector<int> means(K);
for (int i = 0; i < K; i++) {
means[i] = distr(eng);
}
// aqui ele escolhe algum vértice dentro do vetor de vertices pra colocar dentro do vetor means[]


std::vector<int> assignments(N); // centróides escolhidos
for (size_t iteration = 0; iteration < number_of_iterations; ++iteration) { //iterar sobre o número máximo de iterações informados
//Find assignments.
if (iteration > 0)
for (int i = 0; i < k; i++) means[i] = new_means[i];
for (int point = 0; point < N; ++point) {
int best_distance = std::numeric_limits<int>::max();
int best_cluster = 0;
for (int cluster = 0; cluster < k; ++cluster) { // para cada centróide [cluster], achar a mínima distância de cada ponto pra cada centróide
int distance = dado[point][means[cluster]];            //distância do PONTO até o CLUSTER
if (distance == 0) continue; // fugir da distância ser 0. isso prejudica o algoritmo. 0 indica que é um nó ligado a ele mesmo. agnt ignora o loop caso isso aconteça
if (distance < best_distance) {
best_distance = distance;
best_cluster = cluster;
}
}
assignments[point] = best_cluster; // depois de achar a minima distância, atribuir o vértice ao cluster desejado
}
std::vector<int> counts(k, 0);

int sum = 0;
int min = INF;
int newcluster = 0;
for (int i = 0; i < N; i++) {
std::cout << means[assignments[i]] << ' ';
counts[assignments[i]]++;
}

std::cout << std::endl;
for (int i = 0; i < K; i++) {
for (int j = 0; j < N; j++) {
for (int k = 0; k < N; k++) {
if (assignments[j] == i)
sum += dado[j][k];
}
if (sum < min && sum != 0) {
min = sum;
newcluster = j + 1;
}
sum = 0;
}
std::cout << newcluster;
new_means[i] = newcluster;
min = INF;
std::cout << '\n';
}
// Sum up and count points for each cluster.
// aqui agnt vai escolher os novos centróides. o critério vai ser: o nó que chega em todos os outros nós com custo mínimo.
// modificar essa parte, não preciso pegar a média deles. The optimal node is the one that can reach all the other nodes with the lowest travel cost.

}
for (int i = 0; i < N; i++) std::cout << "Nó: " << i + 1 << ' ' << '\t' << "Cluster: " << new_means[assignments[i]] << '\n';
return means; //retorna um vetor de inteiros, os novos centroides escolhidos. esse vetor terá tamanho K.
}

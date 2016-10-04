#include "grafo.h"
Grafo::Grafo(int* aristas, int cantNodos, int cantAristas){ 
	adyacencia = new std::list<Arista>[cantNodos];
	int origen, destino, peso;
	int i = 0;
	while(i < 3*cantAristas){
		origen = aristas[i] -1;
		destino = aristas[i + 1] - 1;
		peso = aristas[i + 2];
		adyacencia[origen].push_back(Arista(destino, peso));
		i = i + 3;
	}
}

Grafo::~Grafo(){
	delete[] adyacencia;
}

std::list<Arista>* Grafo::vecinos(int vertice){
	return &adyacencia[vertice];
}


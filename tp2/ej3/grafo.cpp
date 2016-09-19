#include "grafo.h"
Grafo::Grafo(int* aristas, int cantNodos, int cantAristas){ 
	adyacencia = new std::list<Arista>[cantNodos];
	int origen, destino, peso;
	for(int i = 0; i < cantAristas; i++){
		origen = aristas[i] -1;
		destino = aristas[i + 1] - 1;
		peso = aristas[i + 2];
		adyacencia[origen].push_back(Arista(destino, peso));
	}
}

Grafo::~Grafo(){
	delete[] adyacencia;
}

std::list<Arista>* Grafo::vecinos(int vertice){
	return &adyacencia[vertice];
}


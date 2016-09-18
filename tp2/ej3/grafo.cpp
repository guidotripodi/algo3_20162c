#include "grafo.h"
Grafo::Grafo(int* aristas, int cantNodos, int cantAristas){ 
	adyacencia = new std::list<Arista>[cantNodos];
	int origen, destino, peso;
	for(int i = 0; i < cantAristas; i++){
		origen = aristas[0];
		destino = aristas[1];
		peso = aristas[1];
		adyacencia[origen].push_back(Arista(destino, peso));
	}
}

Grafo::~Grafo(){
	//TODO
}

std::list<Arista>* Grafo::vecinos(int vertice){
	return &adyacencia[vertice];
}


#include "grafo.h"
Grafo::Grafo(long* aristas, long cantNodos, long cantAristas){ 
	adyacencia = new std::list<Arista>[cantNodos];
	long origen, destino, peso;
	long i = 0;
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

std::list<Arista>* Grafo::vecinos(long vertice){
	return &adyacencia[vertice];
}

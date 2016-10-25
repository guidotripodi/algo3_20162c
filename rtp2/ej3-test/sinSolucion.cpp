#include <stdio.h>
#include "grafo.h"
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;
#define MAX_ESTACIONES 50
#define PESO 0

void buscarCaminoMinimo(int cantidad, int vias, int* entrada);
int masCercano(bool* noVisitados, int* distancia, int cantNodos);

int main(){
	
	int maximasVias = MAX_ESTACIONES * (MAX_ESTACIONES - 1);
	maximasVias = maximasVias / 2; //si la precision jode puedo shiftear
	int vias[3*maximasVias];
	
	//caso base
	int cantidadEstaciones = 2;
	int cantidadVias = 0;
	int indiceVias = 0;
		
	for( ; cantidadEstaciones < MAX_ESTACIONES; cantidadEstaciones++){
		auto start = ya();
		buscarCaminoMinimo(cantidadEstaciones, cantidadVias, vias);
		auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
            printf("\n");
		//armar la siguiente iteracion
		int i = 0;
		while(i < cantidadEstaciones - 1){
			//arista desde i al destino
			vias[indiceVias] = i + 1;
			vias[indiceVias + 1] = cantidadEstaciones;
			vias[indiceVias + 2] = PESO;
			i++;
			cantidadVias++;
			indiceVias += 3;
		}
		
	}

	return 0;
}

void buscarCaminoMinimo(int cantidadEstaciones, int cantidadVias, int* vias){	
	Grafo fortaleza = Grafo(vias, cantidadEstaciones, cantidadVias); //fancy arreglo de listas enlazadas

	int distance[cantidadEstaciones];
	int prev[cantidadEstaciones];
	int salida = cantidadEstaciones - 1;	
	//la cola de prioridad, true si ya lo visitamos
	bool noVisitados[cantidadEstaciones];
	
	for(int i = 0; i < cantidadEstaciones; i++){
		distance[i] = -1;
		prev[i] = -1;
		noVisitados[i] = true;
	}

	distance[0] = 0;
	int actual;
	std::list<Arista>* vecinos; 
	std::list<Arista>::iterator posActual;

	while( (actual = masCercano(noVisitados, distance, cantidadEstaciones)) != -1 ){ //O(n)
	
		noVisitados[actual] = false; //lo saco de la "cola"
		if(actual == salida) break; //ya tiene una distancia y prev asignados
		
		vecinos = fortaleza.vecinos(actual);
		for(posActual = vecinos->begin(); posActual != vecinos->end(); ++posActual){ 
			Arista v = *posActual;
			int alt = distance[actual] + v.peso; //si la distancia la guarda el nodo: v.distance;
			if( alt < distance[v.destino] || distance[v.destino] == -1){
				distance[v.destino] = alt;
				prev[v.destino] = actual;
			}

		}
	}

	//recorrer el arreglo prev y ahi tengo los vertices necesarios.
	int j = salida;
	//printf("%d\n", distance[j]);
	if(distance[j] != -1){
		std::list<int> output;
		std::list<int>::iterator itOut;
		while( j >= 0 ){
			output.push_front(j);
			j = prev[j]; //prev[0] esta en -1 entonces ahi corta el ciclo
		}
		//printf( "%lu\n", output.size() );
		for(itOut = output.begin(); itOut != output.end(); ++itOut){ 
		//	printf("%d ", *itOut + 1); //imprimo estaciones
		}
		//printf("\n");
	}
}

int masCercano(bool* noVisitados, int* distancia, int cantNodos){ //O(n)
	int minimo;
	int i = 0;

	//inicializo el minimo con el primer elemento que exista
	//devuelvo -1 si no hay

	while( i < cantNodos ){
		if( noVisitados[i] && distancia[i] != -1){ // no distancia invalida
			minimo = i;
			break;
		}
		i++;
	}

	if(i == cantNodos) return -1; //visite todos y no encontre un minimo

	for(int j = i + 1; j < cantNodos; j++){
		if( distancia[j] < distancia[minimo] &&
				noVisitados[j] &&
				distancia[j] != -1){ // no distancia invalida
			minimo = j;
		}
	}
	return minimo;
}
/*
	function Dijkstra(Graph, source):

	create vertex set Q

	for each vertex v in Graph:             // Initialization
		dist[v] ← INFINITY                  // Unknown distance from source to v
		prev[v] ← UNDEFINED                 // Previous node in optimal path from source
		add v to Q                          // All nodes initially in Q (unvisited nodes)

	dist[source] ← 0                        // Distance from source to source

	while Q is not empty:
		u ← vertex in Q with min dist[u]    // Source node will be selected first
		remove u from Q 

		for each neighbor v of u:           // where v is still in Q.
			alt ← dist[u] + length(u, v)
			if alt < dist[v]:               // A shorter path to v has been found
			dist[v] ← alt 
			prev[v] ← u 

	return dist[], prev[]

If we are only interested in a shortest path between vertices source and target,
we can terminate the search after line 13 if u = target. Now we can read the shortest
path from source to target by reverse iteration:

	S ← empty sequence
	u ← target
	while prev[u] is defined:                  // Construct the shortest path with a stack S
		insert u at the beginning of S         // Push the vertex onto the stack
		u ← prev[u]                            // Traverse from target to source
	insert u at the beginning of S             // Push the source onto the stack
*/


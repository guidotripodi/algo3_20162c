#include <stdio.h>
#include "grafo.h"

//TODO:
//enunciado dice que las estaciones se numeran de 1 a n
//me falta arreglar esos indices para que la salida se imprima correctamente
//destructor del grafo
//embellecimiento
//TESTEO

//capaz usar algo mas piola que cin para la entrada
//con mas control de errores 

int masCercano(bool* noVisitados, int* distancia, int cantNodos){ //O(n)
	int minimo;
	int i = 0;

	//inicializo el minimo con el primer elemento que exista
	//devuelvo -1 si no hay

	while( i < cantNodos ){
		if( noVisitados[i] && distancia[i] != -1){ // no distancia invalida
			minimo = distancia[i];
			break;
		}
		i++;
	}

	if(i == cantNodos) return -1; //visite todos y no encontre un minimo
	
	for(; i < cantNodos; i++){
		if( distancia[i] < minimo && 
				noVisitados[i] &&
				distancia[i] != -1){ // no distancia invalida
			minimo = distancia[i];
			noVisitados[i] = false; //lo saco de la "cola"
		}
	}
	return minimo;
}

int main(){

	int cantidad, vias;

	//parsear stdin
	
	std::cin >> cantidad;
	std::cin >> vias;

	int entrada[3*vias];
	
	for(int i = 0; i < 3*vias; i++){
		std::cin >> entrada[i];
	}

	Grafo fortaleza = Grafo(entrada, cantidad, vias); //fancy arreglo de listas enlazadas


	int distance[cantidad];
	int prev[cantidad];
	int salida = cantidad - 1;	
	//la cola de prioridad, true si ya lo visitamos
	bool noVisitados[cantidad];
	
	for(int i = 0; i < cantidad; i++){
		distance[i] = -1;
		prev[i] = -1;
		noVisitados[i] = true;
	}

	distance[0] = 0;
//Si hago un objeto grafo todo lo de arriba va en el constructor

//no sabemos si el grafo es lo suficientemente esparso para
//usar el min heap y no pasarnos en complejidad de O(n cuadrado)
//asi que la cola se hace con arreglo


	int contador = 0; // cuenta estaciones recorridas

	int actual;
	std::list<Arista>* vecinos; 
	std::list<Arista>::iterator posActual;

	while( (actual = masCercano(noVisitados, distance, cantidad)) != -1 ){//no visitados
		//de los no visitados y ademas lo saca
		//capaz queda mas claro el algoritmo si lo marco visitado al mas cercano aca
		//en lugar de adentro de la funcion masCercano
	
		//if(actual == NULL) break; //visite todo
		if(actual == salida) break; //ya tiene una distancia y prev asignados
		
		vecinos = fortaleza.vecinos(actual);
		for(posActual = vecinos->begin(); posActual != vecinos->end(); ++posActual){ 
		//while(!vecinos.vacia()){
			Arista v = *posActual;
			int alt = distance[v.destino] + v.peso; //si la distancia la guarda el nodo: v.distance;
			if( alt < distance[v.destino] || distance[v.destino] == -1){
				distance[v.destino] = alt;
				prev[v.destino] = actual;
			}

		}
		contador++;
	}

	//recorrer el arreglo prev y ahi tengo los vertices necesarios.
	int j = salida;
	printf("%d\n", distance[j]);
	if(distance[j] != -1){
		printf("%d\n", contador); // tengo que llevar cuenta de los niveles recorridos
		while( j >= 0 ){
			printf("%d", j + 1); //imprimo estaciones
			j = prev[j]; //prev[0] esta en -1 entonces ahi corta el ciclo
		}
	}
	return 0;
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

If we are only interested in a shortest path between vertices source and target, we can terminate the search after line 13 if u = target. Now we can read the shortest path from source to target by reverse iteration:

	S ← empty sequence
	u ← target
	while prev[u] is defined:                  // Construct the shortest path with a stack S
		insert u at the beginning of S         // Push the vertex onto the stack
		u ← prev[u]                            // Traverse from target to source
	insert u at the beginning of S             // Push the source onto the stack
*/


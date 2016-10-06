#include <stdio.h>
#include "grafo.h"


void buscarCaminoMinimo(long cantidad, long vias, long* entrada);
long masCercano(bool* noVisitados, long* distancia, long cantNodos);


int main(){

	long cantidad, vias;

	//parsear stdin
	
	std::cin >> cantidad;
	std::cin >> vias;

	long entrada[3*vias];
	
	for(long i = 0; i < 3*vias; i++){
		std::cin >> entrada[i];
	}

	buscarCaminoMinimo(cantidad, vias, entrada);

	return 0;
}

void buscarCaminoMinimo(long cantidad, long vias, long* entrada){

	Grafo fortaleza = Grafo(entrada, cantidad, vias);
	long distance[cantidad];
	long prev[cantidad];
	long salida = cantidad - 1;	
	//la cola de prioridad, true si ya lo visitamos
	bool noVisitados[cantidad];
	
	for(long i = 0; i < cantidad; i++){
		distance[i] = -1;
		prev[i] = -1;
		noVisitados[i] = true;
	}

	distance[0] = 0;
	long actual;
	std::list<Arista>* vecinos; 
	std::list<Arista>::iterator posActual;

	while( (actual = masCercano(noVisitados, distance, cantidad)) != -1 ){ //O(n)
	
		noVisitados[actual] = false; //lo saco de la "cola"
		if(actual == salida) break; //ya tiene una distancia y prev asignados
		
		vecinos = fortaleza.vecinos(actual);
		for(posActual = vecinos->begin(); posActual != vecinos->end(); ++posActual){ 
			Arista v = *posActual;
			long alt = distance[actual] + v.peso; //si la distancia la guarda el nodo: v.distance;
			if( alt < distance[v.destino] || distance[v.destino] == -1){
				distance[v.destino] = alt;
				prev[v.destino] = actual;
			}

		}
	}

	long j = salida;
	printf("%ld\n", distance[j]);
	if(distance[j] != -1){
		std::list<long> output;
		std::list<long>::iterator itOut;
		while( j >= 0 ){
			output.push_front(j);
			j = prev[j]; //prev[0] esta en -1 entonces ahi corta el ciclo
		}
		printf( "%lu\n", output.size() );
		for(itOut = output.begin(); itOut != output.end(); ++itOut){ 
			printf("%ld ", *itOut + 1); //imprimo estaciones
		}
		printf("\n");
	}
}

long masCercano(bool* noVisitados, long* distancia, long cantNodos){ //O(n)
	long minimo;
	long i = 0;

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

	for(long j = i + 1; j < cantNodos; j++){
		if( distancia[j] < distancia[minimo] &&
				noVisitados[j] &&
				distancia[j] != -1){ // no distancia invalida
			minimo = j;
		}
	}
	return minimo;
}

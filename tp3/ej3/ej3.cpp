#include <iostream>
#include <vector>
#include <algorithm> //debe ser para el swap esto no?
#include <fstream>
#include <utility>
//#include "MaestroPokemon.hpp"
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define ya chrono::high_resolution_clock::now
#define SEED 39
#define MAX_PODER 25
#define RADIO 100

using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

vector<int> mejorar2opt(vector<int> solucionParcial);
vector<int> mejorar3opt(vector<int> solucionParcial);

long long calcularCosto(vector<int> &camino);

int cant_gimnasios, cant_pokeParadas, cap_mochila;

Gimnasio *posiciones_gym_ptr;
Pokeparada *posiciones_pp_ptr;
//nuestros costos son enteros, suma de distancias euclidianas sin tomar raiz cuadrada

int main(){
	//generar entradas
	//srand (time(NULL));
	srand(SEED);
	
	
	Gimnasio posiciones_gym[cant_gimnasios];
	
	bool utilizado[RADIO][RADIO];
	
	for(int i = 0; i < RADIO; i++){
		for(int j = 0; j < RADIO; j++){
			utilizado[i][j] = false;
		}
	}
	
	
	for(int i = 0; i < cant_gimnasios; i++){
		Gimnasio gymPuebloPaleta;//gimnasio (uno solo)
		bool usado = true;
		int x, y;
		while(usado){
			x = rand() % RADIO;
			y = rand() % RADIO;	
			if(!utilizado[x][y]) 
				usado = false;
		}
		gymPuebloPaleta.first.first = x;
		gymPuebloPaleta.first.second = y;
		gymPuebloPaleta.second = rand() % MAX_PODER;
		posiciones_gym[i] = gymPuebloPaleta;
		utilizado[x][y] = true;
	}
	
	cant_pokeParadas = ((MAX_PODER * cant_gimnasios)/3)*2;
	Pokeparada posiciones_pp[cant_pokeParadas];
	
	for(int j = 0; j < cant_pokeParadas; j++){
		Pokeparada posicion;
		bool usado = true;
		int x, y;
		while(usado){
			x = rand() % RADIO;
			y = rand() % RADIO;	
			if(!utilizado[x][y]) 
				usado = false;
		}
		posicion.first = x;
		posicion.second = y;
		posiciones_pp[j] = posicion;
		utilizado[x][y] = true;
	}
	
	posiciones_gym_ptr = posiciones_gym;
	posiciones_pp_ptr = posiciones_pp;
		
	//mejorar solucion
	if(solucionParcial != NULL){
		vector <int> solucionMejorada = mejorar2opt(solucionParcial);
		//imprimir solucion mejorada
	}else{
		printf("%d", -1);
		//no hubo solucion parcial a partir de la cual trabajar
	}

	return 0;
}


//version 2opt
vector<int> mejorar2opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = cant_gimnasios + cant_pokeParadas;//gusanito

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionParcial;
			}

			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return solucion;
}

//version 3opt
vector<int> mejorar3opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = cant_gimnasios + cant_pokeParadas;//gusanito

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {

            swap(solucionParcial[j], solucionParcial[j+1]%n);
			swap(solucionParcial[i], solucionParcial[i+1]);

			long long costoActual = calcularCosto(&solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionParcial;
			}

			swap(solucionParcial[i], solucionParcial[i+1]);//volver al original
			swap(solucionParcial[j], solucionParcial[j+1]%n);//volver al original
		}
	}
	return solucion;
}

bool pasoPosible(int destino, int capacidadParcial){
	//TODO
	Gimnasio gym;

	int poderGym = 0;

	if (destino < cant_gimnasios)
	{
		poderGym = posiciones_gym_ptr[destino].second;
	}
	
	if (poderGym == 0 || capacidadParcial < poderGym)
	{
		return true;
	}
	
	return false;
}

long long distancia(pair<int, int> origen, pair<int, int> destino){
	return pow(origen.first - destino.first, 2) + pow(origen.second - destino.second, 2);//gusanito
}

long long calcularCosto(vector<int> &camino, int capacidadMochila){
	//toda la complejidad del ejercicio es esto en realidad
	long long costo = 0;
	int capacidadParcial = 0;
	for(int i = 1; i < camino->size(); i++){
		if(pasoPosible(camino[i-1], camino[i])){
			
			pair<int, int> pOrigen;
			pair<int, int> pDestino;
			
			int origen = camino[i-1];
			int destino = camino[i];
			
			bool destinoEsPP = false;
			
			if (origen < cant_gimnasios)
			{
				pOrigen = posiciones_gym_ptr[origen].first;
			}else {
				pOrigen = posiciones_pp_ptr[origen-cant_gimnasios];
			}
			
			if (destino < cant_gimnasios)
			{
				pDestino = posiciones_gym_ptr[destino].first;
			}else {
				pDestino = posiciones_pp_ptr[destino-cant_gimnasios];
				destinoEsPP = true;
			}			
			
			costo = costo + distancia(pOrigen, pDestino);
			if(destinoEsPP){
				capacidadParcial += 3;
				if(capacidadParcial > cap_mochila){
					capacidadParcial = cap_mochila;
				}
			}
		} else{
			return -1;
		}
	}
	
	return costo;
}


#include <iostream>	/* printf, cout*/
#include <vector> 
#include <algorithm> //gusanito
#include <fstream>
#include <utility>
#include <chrono>  /* clock */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>	/* pow */
#include <cstdlib> /* swap */
#include <list>
#define ya chrono::high_resolution_clock::now
#define SEED 39
#define MAX_PODER 25
#define RADIO 100
#define TENOR 5 //tenor tabu

using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

vector<int> mejorar2opt(vector<int> solucionParcial);
vector<int> mejorar3opt(vector<int> solucionParcial);

long long calcularCosto(vector<int> &camino);

int cantGyms, cantPokeParadas, capMochila;

Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;
//nuestros costos son enteros, suma de distancias euclidianas sin tomar raiz cuadrada

int main(){
	//generar entradas
	//srand (time(NULL));
	srand(SEED);
	
	
	bool utilizado[RADIO][RADIO];
	
	for(int i = 0; i < RADIO; i++){
		for(int j = 0; j < RADIO; j++){
			utilizado[i][j] = false;
		}
	}
	
	cantGyms = 2;
	Gimnasio gimnasiosArr[cantGyms];
	
	gimnasiosArr[0].first.first = 2;
	gimnasiosArr[0].first.second = 3;
	gimnasiosArr[0].second = 2;
	
	gimnasiosArr[1].first.first = 3;
	gimnasiosArr[1].first.second = 2;
	gimnasiosArr[1].second = 3;
	
	cantPokeParadas = 5;
	Pokeparada pokeParadasArr[cantPokeParadas];
	
	pokeParadasArr[0].first = 0;
	pokeParadasArr[0].second = 0;
	pokeParadasArr[1].first = 0;
	pokeParadasArr[1].second = 1;
	pokeParadasArr[2].first = 1;
	pokeParadasArr[2].second = 1;
	pokeParadasArr[3].first = 2;
	pokeParadasArr[3].second = 2;
	pokeParadasArr[4].first = 1;
	pokeParadasArr[4].second = 3;
	
	capMochila = 8;
	/*
	Gimnasio gimnasiosArr[cantGyms];
	for(int i = 0; i < cantGyms; i++){
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
		gimnasiosArr[i] = gymPuebloPaleta;
		utilizado[x][y] = true;
	}
	
	
	cantPokeParadas = ((MAX_PODER * cantGyms)/3)*2;
	Pokeparada pokeParadasArr[cantPokeParadas];
	
	for(int j = 0; j < cantPokeParadas; j++){
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
		pokeParadasArr[j] = posicion;
		utilizado[x][y] = true;
	}
	*/
	
	gimnasiosArrPtr = gimnasiosArr;
	pokeParadasArrPtr = pokeParadasArr;
	
	vector<int> solucionParcial;
	
	solucionParcial.push_back(2);
	solucionParcial.push_back(3);
	solucionParcial.push_back(5);
	solucionParcial.push_back(0);
	solucionParcial.push_back(6);
	solucionParcial.push_back(1);
	
	long long costo = calcularCosto(solucionParcial);
	
	printf("Costo inicial: %d\n", costo);
	//mejorar solucion
	if( solucionParcial.size()){
		vector <int> solucion2opt= mejorar3opt(solucionParcial);
		//imprimir solucion mejorada
		for(int i = 0; i < (int) solucion2opt.size(); i++){
			printf("%d ", solucion2opt[i]);
		}
		printf("\n");
	}else{
		printf("%d", -1);
		//no hubo solucion parcial a partir de la cual trabajar
	}

	return 0;
}

vector<int> tabuSearch(vector<int> solucionParcial){
	vector<int> solucionActual = solucionParcial;
	vector<int> solucionMejor = solucionParcial;
	list< vector<int> > listaTabu;
			
	while(!condicion de parada){ //TODO
		vector< vector<int> > candidatos;//queda medio feo, lista enlazada?
		vector<int> mejorCandidato;
		//TODO inicializar vecindad!!!
		//de la solucionActual 
		while(vecindad.size() > 0){
			if( !contains(tabuList, candidatoActual) && 
				calcularCosto(candidatoActual) > calcularCosto(mejorCandidato){
				mejorCandidato = candidatoActual;
			}

			candidatoActual = vecindad.front();
			vecindad.pop_front();
		}
		solucionActual = mejorCandidato;
		if(calcularCosto(mejorCandidato) > calcularCosto(mejorSolucion)){
			mejorSolucion = mejorCandidato;
		}
		listaTabu.push_back(mejorCandidato);
		if(tabuList.size() > TENOR) listaTabu.pop_front();

	}
	return solucionMejor;
}



//version 2opt
vector<int> mejorar2opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = cantGyms + cantPokeParadas;//gusanito

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionParcial;
				printf("Costo mejorado: %lld\n", costoActual);
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
	int cantNodos = cantGyms + cantPokeParadas;//gusanito

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {

            swap(solucionParcial[j], solucionParcial[(j+1)% cantNodos] );
			swap(solucionParcial[i], solucionParcial[i+1]);

			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionParcial;
				printf("Costo mejorado: %lld\n", costoActual);
			}

			swap(solucionParcial[i], solucionParcial[i+1]);//volver al original
			swap(solucionParcial[j], solucionParcial[(j+1)% cantNodos] );//volver al original
		}
	}
	return solucion;
}

bool pasoPosible(int destino, int capacidadParcial){
	//TODO
	Gimnasio gym;

	int poderGym = 0;

	if (destino < cantGyms)
	{
		poderGym = gimnasiosArrPtr[destino].second;
	}
	
	if (poderGym == 0 || capacidadParcial > poderGym)
	{
		return true;
	}
	
	return false;
}

long long distancia(pair<int, int> origen, pair<int, int> destino){
	return pow(origen.first - destino.first, 2) + pow(origen.second - destino.second, 2);//gusanito
}

long long calcularCosto(vector<int> &camino){
	//toda la complejidad del ejercicio es esto en realidad
	long long costo = 0;
	int capacidadParcial = 0;
	
	for(int i = 1; i < (int) camino.size(); i++){
		if(pasoPosible(camino[i], capacidadParcial)){
			
			pair<int, int> pOrigen;
			pair<int, int> pDestino;
			
			int origen = camino[i-1];
			int destino = camino[i];
			
			bool destinoEsPP = false;
			
			if (origen < cantGyms)
			{
				pOrigen = gimnasiosArrPtr[origen].first;
			}else {
				pOrigen = pokeParadasArrPtr[origen-cantGyms];
			}
			
			if (destino < cantGyms)
			{
				pDestino = gimnasiosArrPtr[destino].first;
			}else {
				pDestino = pokeParadasArrPtr[destino-cantGyms];
				destinoEsPP = true;
			}			
			
			costo = costo + distancia(pOrigen, pDestino);
			
		//	printf("Distancia de (%d,%d) a (%d,%d) = %lld \n", pOrigen.first, pOrigen.second, pDestino.first, pDestino.second, distancia(pOrigen, pDestino));
			
			if(destinoEsPP){
				capacidadParcial += 3;
				if(capacidadParcial > capMochila){
					capacidadParcial = capMochila;
				}
			}
		} else{
			return -1;
		}
	}
	
	return costo;
}


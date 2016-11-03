#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <cstdlib>
#include "MaestroPokemon.hpp"
#define ya chrono::high_resolution_clock::now
#define SEED 39
#define MAX_PODER 25
#define RADIO 100
#define TEST_ITER 20
using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

//pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);
//vector<int> mejorarSwap(vector<int> solucionParcial);
//vector<int> mejorar2opt(vector<int> solucionParcial);
//vector<int> mejorar3opt(vector<int> solucionParcial);

//Funciones Auxiliares
void optimizarSolucion(vector<int> &solucion);
long long calcularCosto(vector<int> &camino);
//pair<float, float> mediaPodadaVarianzaMuestral(vector<long long> &muestra); 

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

pair<float, float> mediaPodadaVarianzaMuestral(vector<long long> &muestra) 
{
	//asume TEST_ITER divisible por 4
	float alpha = 0.5;
	int n = TEST_ITER;
	int x1, x2;

	x1 = n*alpha/2; //quiero sacar de ambos lados
	x2 = n*alpha/2; 


	sort(muestra.begin(), muestra.end());
	
	for(int i = 0; i < x1; i++)
		muestra.pop_back();

	//for(int i = 0; i < x2; i++)
	//	muestra.pop_front(); pop front no existe!

	long long sum = 0;
	for(int i = x2; i < (int)muestra.size(); i++) sum += muestra[i];
	float mean = (float) sum / (float) (muestra.size() - x2);
	
	float sampleVariance;
	float total = 0.0;
	for(int i = x2; i < (int)muestra.size(); i++)
	{
		sampleVariance = muestra[i] - mean;
		sampleVariance = sampleVariance * sampleVariance;
		total = total + sampleVariance;
	}
	total = total / (float)(muestra.size() - x2);
	total = sqrt(total);

	return make_pair(mean, total);
}
vector<int> mejorarSwap(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			vector<int> solucionOptimizada = solucionParcial; 
			optimizarSolucion(solucionOptimizada);
			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionOptimizada;
				printf("Costo mejorado: %lld\n", costoActual);
			}

			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return solucion;
}

vector<int> mejorar2opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();
	vector<int> solucionOptimizada;
	long long costoActual;

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {

			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
			
			solucionOptimizada = solucionParcial;
			optimizarSolucion(solucionOptimizada);
			costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				costoAnterior = costoActual;
				solucion = solucionOptimizada;
				printf("Costo mejorado: %lld\n", costoActual);
			}
			
			//volver al original
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
		}
	}
	return solucion;
}

/* Mi error fue tratar de asociar el concepto de arista a un nodo (el destino)
 * Al eliminar las 3 aristas que elegimos quedan dos(o tres?) maneras de reconectar el camino
 * sin que sea un camino 2opt. Sean 0 -> a  b->c d->fin aristas y las borramos.
 * Caso1: Reconectamos 0 -> b, a -> d y c -> fin (intervalos (a,b) (c,d) invertidos)
 * Caso2: Reconectamos 0 -> c, d -> a y b -> fin ("swap" de rangos sin invertir)
 * Caso3: Reconectamos 0 -> d, c -> a y b -> fin (swap + invertir rango (c,d))
	 * Caso4: Reconectamos 0 -> c, d -> b y a -> fin (swap + invertir rango (a,b))
	 *
	 * Nota: 0 no es el principio del arreglo y fin no es el fin del arreglo
	 * solo indican principio y fin del subarreglo que deberia cambiar.
	 * TODO: analizar casos borde!!!
	 * Propiedades utiles para la implementacion: 
	 * 0 = a-1
	 * b = c-1
	 * d = fin - 1
	 * me deja usar 3 subindices*/
					
vector<int> mejorar3opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();
	long long costoActual;
	vector<int> solucionOptimizada;
	
	for (int i = 1; i < cantNodos-3; i++) {
		for (int j = i+1; j < cantNodos-2; j++) {
			for (int k = j+2; k < cantNodos; k++) {
				

				//Caso 1
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);
				solucionOptimizada = solucionParcial;
				optimizarSolucion(solucionOptimizada);

				if (costoActual != -1 && costoActual < costoAnterior)
				{
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
					printf("Costo mejorado: %lld\n", costoActual);
				}
			
				printf("Caso 1 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");


				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				//Caso 2

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);
				solucionOptimizada = solucionParcial;
				optimizarSolucion(solucionOptimizada);

				if (costoActual != -1 && costoActual < costoAnterior) 
				{
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}

				printf("Caso 2 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 3
				
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				
				solucionOptimizada = solucionParcial;
				optimizarSolucion(solucionOptimizada);
				costoActual = calcularCosto(solucionOptimizada);

				if (costoActual != -1 && costoActual < costoAnterior) {
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}
				printf("Caso 3 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");
			
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 4
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				solucionOptimizada = solucionParcial;
				optimizarSolucion(solucionOptimizada);
				costoActual = calcularCosto(solucionOptimizada);

				if (costoActual != -1 && costoActual < costoAnterior) {
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}

				printf("Caso 4 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");

				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
			}

		}
	}

	return solucion;
}

bool pasoPosible(int destino, int capacidadParcial){
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
	return 
		pow(origen.first - destino.first, 2) +
		pow(origen.second - destino.second, 2);
}

long long calcularCosto(vector<int> &camino){
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
			} else {
				capacidadParcial = capacidadParcial - gimnasiosArrPtr[destino].second;
			}
		} else{
			return -1;
		}
	}
	
	return costo;
}

void optimizarSolucion(vector<int> &solucion)
{
	int i = solucion.size() -1;
	while(solucion[i] >= cantGyms && i > 0)
	{
		solucion.pop_back();
		i--;
	}
}


pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int>  posiciones_pp[], pair<int,int>  pp_aux[])
{
	int cantidadTotalDePocionesConSuerte = 3 * cant_pokeParadas;
	int pocionesANecesitar = 0;
	for (int i = 0; i < cant_gimnasios; ++i){
		pocionesANecesitar = pocionesANecesitar + posiciones_gym[i].second;
		if (posiciones_gym[i].second > cap_mochila || posiciones_gym[i].second > cantidadTotalDePocionesConSuerte){
			//Sin solucion!
			
			return NULL;
		}
	}
	if(pocionesANecesitar > cantidadTotalDePocionesConSuerte){
			//Sin solucion!

		return NULL;
	}
		
		
	bool posible = true;
	
	int minimo = -1; 
	std::list<int> * camino;


	for (int x = 0; x < cant_pokeParadas + cant_gimnasios; ++x)
	{

		posible = true;
		MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp, x); //Aca se registran en el Pokedex
		while(posible){
			//ash.printStatus();
			if (ash.gane())
			{
				if (ash.distancia < minimo || minimo == -1)
				{
					//cout<<"minimo alcanzado\n";
					minimo = ash.distancia;
					camino = ash.caminoRecorrido(pp_aux);

				}
				
			}

			posible = ash.eleccionGolosa();
			posible = posible && (minimo == -1 || ash.distancia<minimo);
			
		}
	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}

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

using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);
vector<int> mejorarSwap(vector<int> solucionParcial);
vector<int> mejorar2opt(vector<int> solucionParcial);
vector<int> mejorar3opt(vector<int> solucionParcial);

long long calcularCosto(vector<int> &camino);

int cantGyms, cantPokeParadas, capMochila;

Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;
//nuestros costos son enteros, suma de distancias euclidianas sin tomar raiz cuadrada

int main()
{
	
	/*
	//testing
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
	vector<int> solucionParcial;
	
	solucionParcial.push_back(2);
	solucionParcial.push_back(3);
	solucionParcial.push_back(5);
	solucionParcial.push_back(0);
	solucionParcial.push_back(6);
	solucionParcial.push_back(1);
	*/
 
	/*
	//testing aleatorio
	srand(SEED);
	bool utilizado[RADIO][RADIO];
	
	for(int i = 0; i < RADIO; i++){
		for(int j = 0; j < RADIO; j++){
			utilizado[i][j] = false;
		}
	}

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
	cin >> cantGyms >> cantPokeParadas >> capMochila;
	Gimnasio gimnasiosArr[cantGyms];
	for(int i = 0; i < cantGyms; i++)
	{
		Gimnasio gymPuebloPaleta;
		cin >> 
			gymPuebloPaleta.first.first >> 
			gymPuebloPaleta.first.second >>
			gymPuebloPaleta.second;
		gimnasiosArr[i] = gymPuebloPaleta;
	}

	Pokeparada pokeParadasArr[cantPokeParadas];
	Pokeparada pokeParadasAux[cantPokeParadas];
	for(int i = 0; i < cantPokeParadas; i++)
	{
		Pokeparada posicion;
		cin >> posicion.first >> posicion.second;
		pokeParadasArr[i] = posicion;
		pokeParadasAux[i] = posicion;
	}

	pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
			cantGyms, 
			cantPokeParadas,
			capMochila, 
			gimnasiosArr, 
			pokeParadasArr, 
			pokeParadasAux);

	list<int> *solucionInicialLista = solucionInicial->second;
	vector<int> solucionParcial;

	list<int>::iterator itLista;
	for(itLista = solucionInicialLista->begin();
			itLista != solucionInicialLista->end();
			itLista++ )
	{
		solucionParcial.push_back(*itLista);
	}

	gimnasiosArrPtr = gimnasiosArr;
	pokeParadasArrPtr = pokeParadasAux;
	
	
	long long costo = calcularCosto(solucionParcial);
	
	for(int i = 0; i < (int) solucionParcial.size(); i++)
	{
		printf("%d ", solucionParcial[i]);
	}
	printf("\n");
	printf("Costo inicial: %lld\n", costo);
	//mejorar solucion
	if( solucionParcial.size())
	{
		vector <int> solucion2opt= mejorar3opt(solucionParcial);
		for(int i = 0; i < (int) solucion2opt.size(); i++)
		{
			printf("%d ", solucion2opt[i]);
		}
		printf("\n");
	} 
	else{
		printf("%d", -1);
	}

	return 0;
}

/*

un swap puede ser 2opt si swapeo dos consecutivos

1->2->3->4

1->3->2->4

un 3opt puede ser un 2opt si se invierten los intervalos, dado que son contiguos

1->2->3->4->5->6

1->2->4->5->3->6 (ya cambiaron 3 aristas: 2->4 5->3 y 3->6 son las nuevas)

pero si invierto 4->5 

1->2->5->4->3->6 se convierte en un 2opt

un ejemplo similar pero tomando 3->4 y 5 como los intervalos

1->2->5->3->4->6 y ahora si invertimos 3->4 queda

1->2->5->4->3->6 que es un 2opt igual al obtenido tomando 
3 y 4->5 como los intervalos

*/

vector<int> mejorarSwap(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				vector<int> solucionOptimizada = solucionParcial; 
				int i = solucionOptimizada.size() -1;
				while(solucionOptimizada[i] >= cantGyms && i > 0)
				{
					solucionOptimizada.pop_back();
					i--;
				}
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

	long long costoActual;
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {

			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
			costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				vector<int> solucionOptimizada = solucionParcial;
				int i = solucionOptimizada.size() -1;
				while(solucionOptimizada[i] >= cantGyms && i > 0)
				{
					solucionOptimizada.pop_back();
					i--;
				}
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
	
	
	for (int i = 1; i < cantNodos-3; i++) {
		for (int j = i+1; j < cantNodos-2; j++) {
			for (int k = j+2; k < cantNodos; k++) {
				
				//rango 1: i a j
				//rango 2: j+1 a k 

				//Caso 1
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior)
				{
					vector<int> solucionOptimizada = solucionParcial;
					int i = solucionOptimizada.size() -1;
					while(solucionOptimizada[i] >= cantGyms && i > 0)
					{
						solucionOptimizada.pop_back();
						i--;
					}
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

				if (costoActual != -1 && costoActual < costoAnterior) 
				{
					vector<int> solucionOptimizada = solucionParcial;
					int i = solucionOptimizada.size() -1;
					while(solucionOptimizada[i] >= cantGyms && i > 0)
					{
						solucionOptimizada.pop_back();
						i--;
					}
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
				
				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior) {
					vector<int> solucionOptimizada = solucionParcial;
					int i = solucionOptimizada.size() -1;
					while(solucionOptimizada[i] >= cantGyms && i > 0)
					{
						solucionOptimizada.pop_back();
						i--;
					}
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

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior) {
					vector<int> solucionOptimizada = solucionParcial;
					int i = solucionOptimizada.size() -1;
					while(solucionOptimizada[i] >= cantGyms && i > 0)
					{
						solucionOptimizada.pop_back();
						i--;
					}
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
	return pow(origen.first - destino.first, 2) + pow(origen.second - destino.second, 2);//gusanito
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
		
		
	bool exitoBack = true;
	
	int minimo = -1; 
	std::list<int> * camino;


	for (int x = 0; x < cant_pokeParadas; ++x)
	{

		exitoBack = true;
		MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
		while(exitoBack){
			ash.printStatus();
			if (ash.gane())
			{
				if (ash.distancia < minimo || minimo == -1)
				{
				//	cout<<"fin de rama\n";
					minimo = ash.distancia;
					camino = ash.caminoRecorrido(pp_aux);

				}
				
			}

			MaestroPokemon::Eleccion eleccion = ash.eleccionPosible();
				//Si hay un par posible y si la rama que estoy evaluando
				//me sigue dando una mejor solucion a la ya encontrada

			if (eleccion.posible==1 && (minimo == -1 || ash.distancia<minimo))
			{
				//printf("La eleccion tiene una distancia: %d \n",eleccion.distancia );

				//ash.printEleccion(eleccion);
				if(ash.eleccionMinimaPosible(eleccion)){
				//	printf("Elegi: ---- ");
				//	ash.printEleccion(eleccion);
					ash.elegir(eleccion);
					
				}
				
			}else{
				//printf("No fue minima\n");
				exitoBack = false;
			}
		}
		pair <int, int> posicion;
		for (int h = 0; h < cant_pokeParadas; ++h){
			/*Luego de la vuelta completa reordeno el array pp pasando al primer pp al ultimo y 
			muevo todo de esta forma me garantizo que todas las pp van a tener su rama como inicial*/
			if (h == 0)	{
				posicion.first = posiciones_pp[cant_pokeParadas-1].first; 
				posicion.second = posiciones_pp[cant_pokeParadas-1].second; 
			//	printf("Posicion : %d posicion: %d \n",posicion.first, posicion.second );
				posiciones_pp[cant_pokeParadas-1].first = posiciones_pp[0].first;
				posiciones_pp[cant_pokeParadas-1].second = posiciones_pp[0].second;
				posiciones_pp[0].first = posiciones_pp[1].first;
				posiciones_pp[0].second = posiciones_pp[1].second;
			}else{
				if (h+1 < cant_pokeParadas-1)	{
					posiciones_pp[h].first = posiciones_pp[h+1].first;
					posiciones_pp[h].second = posiciones_pp[h+1].second;
					
				}else{
					posiciones_pp[cant_pokeParadas-2].first = posicion.first;
					posiciones_pp[cant_pokeParadas-2].second = posicion.second;
				
				}
			}
		}

	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}

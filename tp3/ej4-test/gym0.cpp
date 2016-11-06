#include <iostream>	/* printf, cout*/
#include <vector> 
#include <algorithm> 
#include <fstream>
#include <utility>
#include <chrono>  /* clock */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>	/* pow */
#include <cstdlib> /* swap */
#include <list>
#include "ej4.hpp"

#define ya chrono::high_resolution_clock::now
using namespace std;

//variables globales definidas en ej4.hpp

#define TEST_ITER 20 

int main(){
	
	int j = 8;
	cantGyms = j+1;
	cantPokeParadas = j;
	pair <pair<int,int>, int> gimnasiosArr[cantGyms];
	pair <int, int>  pokeParadasArr[cantPokeParadas];
	pair <int, int>  pokeParadasAux[cantPokeParadas];
/*	
	vector<long long> tiemposSwap(TEST_ITER);
	vector<long long> tiempos2opt(TEST_ITER);
	vector<long long> tiempos3opt(TEST_ITER);
	
	vector<int> solucionSwap;
	vector<int> solucion2opt;
	vector<int> solucion3opt;
*/
	
	vector<long long> tiempos(TEST_ITER);
	vector<int> solucionMejorada;
	vector<int> solucionParcial;
	
	int i = 0;
	for (i = 0; i < cantGyms; i++)
	{
		Gimnasio gymPuebloPaleta;
		gymPuebloPaleta.first.first = i;
		gymPuebloPaleta.first.second = i+1;
		if( i % 2 == 0)
		{
			gymPuebloPaleta.second = 0;
		} else
		{
			gymPuebloPaleta.second  = i;
		}
		gimnasiosArr[i] = gymPuebloPaleta;
	}
	for (i = 0; i < cantPokeParadas; i++)
	{
		Pokeparada posicion;
		posicion.first = i;
		posicion.second = i+2;
		pokeParadasArr[i] = posicion;
		pokeParadasAux[i] = posicion;
	}
	
	capMochila = cantGyms*3;

	//Llamada a la heuristica(ej2)
	pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
			cantGyms, 
			cantPokeParadas,
			capMochila, 
			gimnasiosArr, 
			pokeParadasArr, 
			pokeParadasAux);


	list<int> *solucionInicialLista = solucionInicial->second;

	list<int>::iterator itLista;
/*
	for(itLista = solucionInicialLista->begin();
			itLista != solucionInicialLista->end();
			itLista++ )
	{
		printf("%d ", *itLista);
	}
	cout << "\n";
*/
	for(itLista = solucionInicialLista->begin();
			itLista != solucionInicialLista->end();
			itLista++ )
	{
		solucionParcial.push_back(*itLista);
	}

	gimnasiosArrPtr = gimnasiosArr;
	pokeParadasArrPtr = pokeParadasAux;
	
	for(int it = 0; it < TEST_ITER; it++)
	{
		//mejorar solucion
		if( solucionParcial.size())
		{
			auto start = ya();
			solucionMejorada = tabuSearch(solucionParcial);
			auto end = ya();
			tiempos[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
		} 
		else{
			printf("%d", -1);
		}

	}

	pair <float, float> estadisticasSwap = mediaPodadaVarianzaMuestral(tiempos);
	//pair <float, float> estadisticas2opt = mediaPodadaVarianzaMuestral(tiempos2opt);
	//pair <float, float> estadisticas3opt = mediaPodadaVarianzaMuestral(tiempos3opt);

	long long mejora = calcularCosto(solucionParcial) - calcularCosto(solucionMejorada);
	//long long mejora2opt = calcularCosto(solucionParcial) - calcularCosto(solucion2opt);
	//long long mejora3opt = calcularCosto(solucionParcial) - calcularCosto(solucion3opt);

/*
	cout << estadisticasSwap.first << " " 
		<< estadisticasSwap.second << " "
		<< mejoraSwap << "\n";

	for(int i = 0; i < (int) solucionSwap.size(); i++) 
		cout << solucionSwap[i] << " ";
	cout << "\n";

	
	cout << estadisticas2opt.first << " "
		<< estadisticas2opt.second << " "
		<< mejora2opt << "\n";

	for(int i = 0; i < (int) solucion2opt.size(); i++) 
		cout << solucion2opt[i] << " ";
	cout << "\n";

	
	cout << estadisticas3opt.first << " "
		<< estadisticas3opt.second << " " 
		<< mejora3opt << "\n";
	for(int i = 0; i < (int) solucion3opt.size(); i++) 
		cout << solucion3opt[i] << " ";
	cout << "\n";
*/
	/*
	cout << calcularCosto(solucionParcial) << " "
		<< calcularCosto(solucionSwap) << " "
		<< calcularCosto(solucion2opt) << " "
		<< calcularCosto(solucion3opt) << "\n";
	*/

	delete solucionInicial;
	return 0;
}


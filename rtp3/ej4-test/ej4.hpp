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
#include "SetTabu.hpp"
#include "MaestroPokemon.hpp"

#define MAX_PODER 25
#define RADIO 100

#define TEST_ITER 20

#define ya chrono::high_resolution_clock::now

using namespace std;

//Tipos
typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;
typedef pair<int,int> Arista;

//Funciones importantes
pair< pair< long long, long long>, long long >  testear(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);

pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);

vector<int> tabuSearch(vector<int> solucionParcial, long long it);

list< pair< vector<int>, list<Arista> > > vecindadSwap(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad2opt(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad3opt(vector<int> solucionParcial);

//auxiliares
pair<float, float> estadisticas(vector<long long> &muestra); 

pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad);

int tabuCount(SetTabu atributos, vector<int> solucion);

long long calcularCosto(vector<int> &camino);

void optimizarSolucion(vector<int> &solucion);

//variables globales
extern int cantGyms, cantPokeParadas, capMochila;
extern Gimnasio *gimnasiosArrPtr;
extern Pokeparada *pokeParadasArrPtr;

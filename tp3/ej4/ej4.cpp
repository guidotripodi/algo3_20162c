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
#define ITERMAX 10
using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

vector<int> tabuSearch(vector<int> solucionParcial);
list< vector<int> > vecindadSwap(vector<int> solucionParcial);
list< vector<int> > vecindad2opt(vector<int> solucionParcial);
list< vector<int> > vecindad3opt(vector<int> solucionParcial);

//probaclemente haya una funcion en la std para esto pero fue
bool contains(list< vector<int> > lista, vector<int> solucion);

long long calcularCosto(vector<int> &camino);

int cantGyms, cantPokeParadas, capMochila;

Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

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
	
	printf("Costo inicial: %lld\n", costo);
	//mejorar solucion
	if(solucionParcial.size()){
		vector <int> mejorada = tabuSearch(solucionParcial);
		//imprimir solucion mejorada
		costo = calcularCosto(mejorada);
		for(int i = 0; i < (int) mejorada.size(); i++){
			printf("%d ", mejorada[i]);
		}
		printf("\n");
		printf("Costo final: %lld\n", costo);
	}else{
		printf("%d", -1);
		//no hubo solucion parcial a partir de la cual trabajar
	}

	return 0;
}

//http://crema.di.unimi.it/~righini/Didattica/Algoritmi%20Euristici/MaterialeAE/Taratura%20parametri%20TS.pdf
//http://www.uv.es/rmarti/paper/docs/ts1.pdf
vector<int> tabuSearch(vector<int> solucionParcial){
	vector<int> solucionActual = solucionParcial;
	vector<int> mejorSolucion= solucionParcial;
	list< vector<int> > listaTabu;
	int iteraciones = 0;			
	while(iteraciones < ITERMAX){
		//vector< vector<int> > candidatos; 
		//esta linea aparece en wikipedia pero no se usa. 
		//Supongo que representa la lista de vecinos?
		vector<int> mejorCandidato;
		list< vector<int> > vecindad = vecindad2opt(solucionActual); 
		// podemos hacer union entre 2opt y 3opt
		
		while(vecindad.size() > 0){
			vector<int> candidatoActual = vecindad.front();
			long long costoActual = calcularCosto(candidatoActual);
			long long costoMejor = calcularCosto(mejorCandidato);

			// contains deberia determinar si una solucion es tabu observando
			// atributos (por recencia o frecuencia) como por ejemplo 
			// ejes no deseables o algo por el estilo
			// y ademas determinar que atributos son tabu activos
			// luego una solucion no visitada puede ser tabu segun los atributos tabu activos
			// hay que determinar que atributos sirven para clasificar
			// utilizamos long term memory 
			// porque no nos concentramos solamente en un subconjunto de una vecindad, 
			// si no en sucesivas vecindades.
			// Cuando todas las soluciones disponibles en la vecindad analizada son tabu active:
			// hay que elegir la menos tabu de todas o la que aun siendo tabu mejore la funcion objetivo
			// 
			if(!contains(listaTabu, candidatoActual) && 
				(costoActual < costoMejor || costoMejor == -1)){
				// funcion de aspiracion A(listaTabu, candidatoActual) = 
				// el menos tabu de los tabu o 
				mejorCandidato = candidatoActual;
			}

			vecindad.pop_front();
		}
		solucionActual = mejorCandidato;
		if(calcularCosto(mejorCandidato) < calcularCosto(mejorSolucion)){
			mejorSolucion = mejorCandidato;
		}
		listaTabu.push_back(mejorCandidato);
		if(listaTabu.size() > TENOR) listaTabu.pop_front();

		iteraciones++;
	}
	return mejorSolucion;
}


list< vector<int> > vecindadSwap(vector<int> solucionParcial){
	list< vector<int> > soluciones;
	//int cantNodos = cantGyms + cantPokeParadas;//al final era gusanito!!
	int cantNodos = solucionParcial.size();
    long long costoActual; 
	for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1) {
				soluciones.push_back(solucionParcial);
			}
			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return soluciones;
}

//version 2opt
list< vector<int> > vecindad2opt(vector<int> solucionParcial){
	list< vector<int> > soluciones;
	//int cantNodos = cantGyms + cantPokeParadas;//al final era gusanito!!
	int cantNodos = solucionParcial.size();
	long long costoActual; 
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);

			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1) {
				soluciones.push_back(solucionParcial);
			}
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
		}
	}
	return soluciones;
}

//version 3opt
list< vector<int> > vecindad3opt(vector<int> solucionParcial){
	list< vector<int> > soluciones;
	int cantNodos = cantGyms + cantPokeParadas;//gusanito
	long long costoActual; 
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
			for (int k = j+1; k < cantNodos; k++) {

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j+1, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);

				if ( costoActual != -1 ){
					soluciones.push_back(solucionParcial);
				}
				
				reverse(solucionParcial.begin() + j+1, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);

				
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				costoActual = calcularCosto(solucionParcial);

				if ( costoActual != -1 ){
					soluciones.push_back(solucionParcial);
				}

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
			}
		}
	}
	return soluciones;
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
	//toda la complejidad del ejercicio es esto en realidad
	long long costo = 0;
	int capacidadParcial = 0;
	
	if(camino.size() == 0 ) return -1;//vector vacio

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

bool contains(list< vector<int> > lista, vector<int> solucion){
	list< vector<int> >::iterator it;
	for(it = lista.begin(); it != lista.end(); it++){
		if(*it == solucion) return true;//gusanito
	}
	return false;
}


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
#include "setTabu.h"

#define ya chrono::high_resolution_clock::now
#define SEED 39
#define MAX_PODER 25
#define RADIO 100
#define TENOR 5 //tenor tabu
#define ITERMAX 10
using namespace std;

//Tipos
typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;
typedef pair<int,int> Arista;

//Funciones importantes
vector<int> tabuSearch(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindadSwap(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad2opt(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad3opt(vector<int> solucionParcial);

//auxiliares
pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad);
int tabuCount(SetTabu atributos, vector<int> solucion);
long long calcularCosto(vector<int> &camino);

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

int main(){
	//generar entradas
	//srand (time(NULL));
	srand(SEED);
	
	
/*	bool utilizado[RADIO][RADIO];
	
	for(int i = 0; i < RADIO; i++){
		for(int j = 0; j < RADIO; j++){
			utilizado[i][j] = false;
		}
	}
*/	
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
vector<int> tabuSearch(vector<int> solucionParcial)
{
	vector<int> solucionActual = solucionParcial;
	vector<int> mejorSolucion= solucionParcial;
	long long costoMejor = calcularCosto(mejorSolucion);
	long long costoMejorVecino;
	SetTabu atributosTabu;
	int iteraciones = 0;			
	while(iteraciones < ITERMAX)
	{
		vector<int> mejorCandidato;
		list<Arista> aristasModificadas; 
		//cada solucion esta asociada a las aristas que cambiaron
		list< pair< vector<int>, list<Arista> > > vecindad = vecindad2opt(solucionActual);
		// podemos hacer union entre 2opt y 3opt
		if(vecindad.size() == 0) return mejorSolucion; //Esto es por las moscas. No deberia pasar	
		
		list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad; 
		for(iteradorVecindad = vecindad.begin(); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
		{
			vector<int> candidatoActual = iteradorVecindad->first;
			long long costoActual = calcularCosto(candidatoActual);
			costoMejorVecino = calcularCosto(mejorCandidato);

			// utilizamos long term memory 
			// porque no nos concentramos solamente en un subconjunto de una vecindad, 
			// si no en sucesivas vecindades.
			// Cuando todas las soluciones disponibles en la vecindad analizada son tabu active:
			// hay que elegir la menos tabu de todas o la que aun siendo tabu mejore la funcion objetivo
			
			if(	costoActual < costoMejor ||
				(!tabuCount(atributosTabu, candidatoActual) && 
				(costoActual < costoMejorVecino || costoMejorVecino == -1)))
			{
				// funcion de aspiracion A(listaTabu, candidatoActual) = 
				// el menos tabu de los tabu o 
				aristasModificadas = iteradorVecindad->second;
				mejorCandidato = candidatoActual;
			}

		}
		
		if(mejorCandidato.size() == 0)
		{
			//no encontre un vecino no tabu
			pair< vector<int>, list<Arista> > menosTabu = funcionAspiracion(atributosTabu, vecindad);
			mejorCandidato = menosTabu.first;
			//Hay que marcar las aristas que se usaron para esta solucion como tabu
			aristasModificadas = menosTabu.second;
		}

		solucionActual = mejorCandidato;
		if(costoMejorVecino < costoMejor)
		{
			mejorSolucion = mejorCandidato;
			costoMejor = costoMejorVecino;
		}
		
		list<Arista>::iterator it;
		for(it = aristasModificadas.begin(); it != aristasModificadas.end(); it++)
		{
			atributosTabu.push(*it);
		}
		
		//TODO es posta el mejor para borrar?
		//el orden en el que se guardan los objetos
		//no es cronologico como la lista.
		while(atributosTabu.size() > TENOR) 
		{
			atributosTabu.pop();
		}

		iteraciones++;
	}

	return mejorSolucion;
}

pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad)
{
	pair< vector<int>, list<Arista> > solucionMenosTabu = vecindad.front();
	int menorCantidad = tabuCount(atributosTabu, solucionMenosTabu.first);
	list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad;
	
	for(iteradorVecindad = next(vecindad.begin(), 1); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
	{
		int cantidadAtributos = tabuCount(atributosTabu, iteradorVecindad->first); 
		if( cantidadAtributos < menorCantidad )
		{
			solucionMenosTabu = *iteradorVecindad;
			menorCantidad = cantidadAtributos;
		}
	}
	return solucionMenosTabu;
}

list< pair< vector<int>, list<Arista> > > vecindadSwap(vector<int> solucionParcial)
{
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
    long long costoActual; 
	for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            list<Arista> aristasModificadas;
			
			//en un swap cambian cuatro aristas
			//quiero guardar las aristas antes de que sean modificadas
			//TODO casos borde, o quizas no; el set tabu me los va a planchar si meto cosas repetidas aca.
			aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
			aristasModificadas.push_back( Arista( solucionParcial[i], solucionParcial[i+1]) );
			aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
			aristasModificadas.push_back( Arista( solucionParcial[(j-1)%cantNodos], solucionParcial[j]) );
			
			swap(solucionParcial[i], solucionParcial[j]);

			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1)
			{
				pair< vector<int>, list<Arista> > solucionConAtributos;
				solucionConAtributos.first = solucionParcial;
				solucionConAtributos.second = aristasModificadas;
				soluciones.push_back(solucionConAtributos);
			}
			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return soluciones;
}

//version 2opt
list< pair< vector<int>, list<Arista> > > vecindad2opt(vector<int> solucionParcial)
{
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
	long long costoActual; 
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            list<Arista> aristasModificadas;
			
			//en un swap cambian cuatro aristas
			//quiero guardar las aristas antes de que sean modificadas
			//TODO casos borde, o quizas no; el set tabu me los va a planchar si meto cosas repetidas aca.
			aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
			aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
			
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);

			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1) 
			{
				pair< vector<int>, list<Arista> > solucionConAtributos;
				solucionConAtributos.first = solucionParcial;
				solucionConAtributos.second = aristasModificadas;
				soluciones.push_back(solucionConAtributos);
			}
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
		}
	}
	return soluciones;
}

//version 3opt
list< pair< vector<int>, list<Arista> > > vecindad3opt(vector<int> solucionParcial){
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
	long long costoActual; 
	
	for (int i = 1; i < cantNodos-3; i++) {
		for (int j = i+1; j < cantNodos-2; j++) {
			for (int k = j+2; k < cantNodos; k++) {
				
				list<Arista> aristasModificadas;
				//Caso 1
				aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[j+1]) );
				aristasModificadas.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionParcial;
					solucionConAtributos.second = aristasModificadas;
					//3opt modifica 3 aristas
					soluciones.push_back(solucionConAtributos);
				}
			
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				//Caso 2

				list<Arista> aristasModificadas2;
				aristasModificadas2.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas2.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas2.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);


				if (costoActual != -1) 
				{
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionParcial;
					solucionConAtributos.second = aristasModificadas2;
					soluciones.push_back(solucionConAtributos);
				}

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 3
				
				list<Arista> aristasModificadas3;
				aristasModificadas3.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas3.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas3.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				
				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionParcial;
					solucionConAtributos.second = aristasModificadas3;
					soluciones.push_back(solucionConAtributos);
				}
				
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 4
				list<Arista> aristasModificadas4;
				aristasModificadas4.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas4.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas4.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionParcial;
					solucionConAtributos.second = aristasModificadas4;
					soluciones.push_back(solucionConAtributos);
				}

				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
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

//en vez de decir si una funcion es tabu o no, cuenta cuantos
//atributos tabu tiene.
int tabuCount( SetTabu atributos, vector<int> solucion )
{
	int tabuAtributeCount = 0;
	vector<int>::iterator itSolucion;
	for(itSolucion = solucion.begin(); itSolucion != solucion.end()-1; itSolucion++){

		if(atributos.belongs( Arista(*itSolucion, *(itSolucion+1)) ))
		{
			tabuAtributeCount++;
		} 
		else
		{
			Arista inversa = Arista(*(itSolucion+1), *itSolucion);
			if(atributos.belongs(inversa)) tabuAtributeCount++;
		}

	}

	if(atributos.belongs( Arista( *itSolucion, *solucion.begin() ) ))
		//mas parentesis que lisp
		tabuAtributeCount++;
	return 0;
}


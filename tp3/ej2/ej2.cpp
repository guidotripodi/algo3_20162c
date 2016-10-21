//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include <utility>
#include "MaestroPokemon.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
using namespace std;


pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[]);

int main(int argc, char* argv[])
{
	int cant_gimnasios, cant_pokeParadas, cap_mochila;
	cin >> cant_gimnasios >> cant_pokeParadas >> cap_mochila;


	pair <pair<int,int>, int> posiciones_gym[cant_gimnasios];
	pair <int, int>  posiciones_pp[cant_pokeParadas];

	int i = 0;
	for (i = 0; i < cant_gimnasios; i++){
		pair <pair<int,int>, int> gymPuebloPaleta;
		
		cin >> gymPuebloPaleta.first.first >> gymPuebloPaleta.first.second >> gymPuebloPaleta.second;
		posiciones_gym[i] = gymPuebloPaleta;
		
	}
	for (i = 0; i < cant_pokeParadas; i++)	{
		pair <int, int> posicion;
		
		cin >> posicion.first >> posicion.second;
		
		posiciones_pp[i] = posicion;
		
	}

	pair <int,std::list<int> * > * f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp);
	
	if ( f == NULL)	{
		cout << "-1" << "\n";
		return -1; 
	}
	cout << f->first <<" "<< f->second->size();
	for (std::list<int>::iterator it=f->second->begin(); it != f->second->end(); ++it){
		cout << " " << *it;

	}
	cout << "\n";
	return 0;
}

 pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int>  posiciones_pp[])
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
		
		printf("HOLA");
	bool exitoBack = true;
	
	int minimo = -1; 
	MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
	std::list<int> * camino;
	while(exitoBack){
		ash.printStatus();
		if (ash.gane())
		{
			if (ash.distancia < minimo || minimo == -1)
			{
			//	cout<<"fin de rama\n";
				minimo = ash.distancia;
				camino = ash.caminoRecorrido();

			}
			
		}

		MaestroPokemon::Eleccion eleccion = ash.eleccionPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada

		if (eleccion.posible==1 && (minimo == -1 || ash.distancia<minimo))
		{
			//printf("La eleccion tiene una distancia: %d \n",eleccion.distancia );

			ash.printEleccion(eleccion);
			if(ash.eleccionMinimaPosible(eleccion)){
				ash.printEleccion(eleccion);
				ash.elegir(eleccion);
				
			}
			
		}else{
			exitoBack = false;
		}
	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}

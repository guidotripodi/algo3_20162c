//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include <utility>
#include "MaestroPokemon.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
#define cantMaxGym 101
#define cantMaxPP 100
using namespace std;


pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[]);

int main(int argc, char* argv[])
{
/*Caso con GYM con 0:*/
	int cant_gimnasios = 0; 
	int cant_pokeParadas = 0;
	int cap_mochila = 0;
	
	for(int j = 4; j < 8; j++){
		cant_gimnasios = j+1;
		cant_pokeParadas = j;
		
		pair <pair<int,int>, int> posiciones_gym[cant_gimnasios];
		pair <int, int>  posiciones_pp[cant_pokeParadas];
		
		int i = 0;
			for (i = 0; i < cant_gimnasios; i++){
			pair <pair<int,int>, int> gymPuebloPaleta;
			gymPuebloPaleta.first.first = i;
			gymPuebloPaleta.first.second = i+1;
			if (i % 2 == 0)	{
				gymPuebloPaleta.second = 0;
			}else{
				gymPuebloPaleta.second = i;
			}
			//algun gym no necesita pociones para ser vencido puntualmente todos los i pares
			//cantidad_pociones_necesarias_total += i*3;
			posiciones_gym[i] = gymPuebloPaleta;
			
		}
		for (i = 0; i < cant_pokeParadas; i++)	{
			pair <int, int> posicion;
			posicion.first = i;
			posicion.second = i+2;
			posiciones_pp[i] = posicion;
		}
		
		cap_mochila = cant_gimnasios*3;
		/*IMPRIMO EN PANTALLA EL CASO: */

		cout << "\n" << "j es:" << j << "\n";
		
		printf("%d %d %d \n", cant_gimnasios, cant_pokeParadas, cap_mochila);
		
		for(i = 0; i < cant_gimnasios; i++){
			printf("%d %d %d \n", posiciones_gym[i].first.first, posiciones_gym[i].first.second, posiciones_gym[i].second );
			}
			
		for(i = 0; i < cant_pokeParadas; i++){
			printf("%d %d\n", posiciones_pp[i].first, posiciones_pp[i].second);
			
			}

			/*Ejecuto el algoritmo*/
			//printf("Estoy aca\n");
		pair <int,std::list<int> * > * f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp);
	
	/*IMPRIMO EN PANTALLA EL RESULTADO:*/
		if ( f == NULL || f->first == -1)	{
			cout << "-1" << "\n";
			//return -1;
		}else{
			cout << f->first <<" "<< f->second->size();
			for (std::list<int>::iterator it=f->second->begin(); it != f->second->end(); ++it){
				cout << " " << *it;
			}
		}
				
		//delete f;
	}
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
	
	bool exitoBack = true;
	
	int minimo = -1; 
	MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
	std::list<int> * camino;
	while(exitoBack){
		//ash.printStatus();
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

			//ash.printEleccion(eleccion);
			ash.elegir(eleccion);
		}else{
				//vuelve al paso anterior
			//cout << "Backtrack \n" ;
			exitoBack = ash.deshacerEleccion();
		}
	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}
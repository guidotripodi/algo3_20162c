//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include <utility>
#include "MaestroPokemon.hpp"
#include <chrono>
#define cantMaxGym 101
#define cantMaxPP 100
#define ya chrono::high_resolution_clock::now
using namespace std;



pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);

int main(int argc, char* argv[])
{
	/*int cant_gimnasios, cant_pokeParadas, cap_mochila;
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
		
	}*/

	/*Caso sin solucion:*/
	int cant_gimnasios = 0; 
	int cant_pokeParadas = 0;
	int cap_mochila = 0;
	pair <pair<int,int>, int> posiciones_gym[cantMaxGym];
	pair <int, int>  posiciones_pp[cantMaxPP];
	pair <int, int>  pp_aux[cantMaxPP];
	
	for(int j = 4; j < 50; j++){
		cant_gimnasios = j+1;
		cant_pokeParadas = j;
		
		int i = 0;
			for (i = 0; i < cant_gimnasios; i++){
			pair <pair<int,int>, int> gymPuebloPaleta;
			gymPuebloPaleta.first.first = i;
			gymPuebloPaleta.first.second = i+1;
			gymPuebloPaleta.second = (i+1)*3;
			//cantidad_pociones_necesarias_total += i*3;
			posiciones_gym[i] = gymPuebloPaleta;
			
		}
		for (i = 0; i < cant_pokeParadas; i++)	{
			pair <int, int> posicion;
			posicion.first = i;
			posicion.second = i+2;
			posiciones_pp[i] = posicion;
			pp_aux[i] = posicion;
		}
		/*ACA LA MOCHILA SOPORTA LA CAPACIDAD MAXIMA PARA AVANZAR POR TODOS, SE VAN A HACER DOS TESTEOS SIN SOLUCION YA QUE TENEMOS DOS PODAS*/
		cap_mochila = cantMaxGym*3	;
		/*
		printf("%d %d %d \n", cant_gimnasios, cant_pokeParadas, cap_mochila);
		
		for(i = 0; i < cant_gimnasios; i++){
			printf("%d %d %d \n", posiciones_gym[i].first.first, posiciones_gym[i].first.second, posiciones_gym[i].second );
			}
			
		for(i = 0; i < cant_pokeParadas; i++){
			printf("%d %d\n", posiciones_pp[i].first, posiciones_pp[i].second);
			
			}*/
		auto start = ya();
		pair <int,std::list<int> * > * f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp, pp_aux);
		auto end = ya();
			    cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
				cout << "\n";
		/*if ( f == NULL || f->first == -1)	{
			cout << "-1" << "\n";
			//return -1;
		}else{
			//cout << f->first <<" "<< f->second->size();
			for (std::list<int>::iterator it=f->second->begin(); it != f->second->end(); ++it){
				cout << *it << " ";
			}
			cout << "\n";
		}*/
		
		
		
		
		delete f;
	}
	return 0;
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

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
	for (int j = 0; j < 50; ++j)
	{
		int cant_gimnasios, cant_pokeParadas, cap_mochila;
		cin >> cant_gimnasios >> cant_pokeParadas >> cap_mochila;


		pair <pair<int,int>, int> posiciones_gym[cant_gimnasios];
		pair <int, int>  posiciones_pp[cant_pokeParadas];
		pair <int, int>  pp_aux[cant_pokeParadas];

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
			pp_aux[i] = posicion;
			
		}
		cout << "j es:" << j << "\n"; 
		printf("%d %d %d \n", cant_gimnasios, cant_pokeParadas, cap_mochila);
		
		for(i = 0; i < cant_gimnasios; i++){
			printf("%d %d %d \n", posiciones_gym[i].first.first, posiciones_gym[i].first.second, posiciones_gym[i].second );
			}
			
		for(i = 0; i < cant_pokeParadas; i++){
			printf("%d %d\n", posiciones_pp[i].first, posiciones_pp[i].second);
			
			}

		pair <int,std::list<int> * > * f;
//			for (int h = 0; h < 20; ++h){
//				auto start = ya();	
				f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp, pp_aux);
//				auto end = ya();
//				if (h == 19)	{
//					cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
//					cout << "\n";
//				}
//			}
	
		if ( f == NULL || f->first == -1)	{
			cout << "-1" << "\n";
			//return -1;
		}else{
			cout << f->first <<" "<< f->second->size();
			for (std::list<int>::iterator it=f->second->begin(); it != f->second->end(); ++it){
				cout << " " << *it;
			}
		}
		cout << "\n";
		
		
		
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

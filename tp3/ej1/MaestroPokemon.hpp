#include <list>
#include <algorithm>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "trie.cpp"

#define GIMNASIO 0
#define PP 1

using namespace std;

class MaestroPokemon {

private:
	//Guardo la eleccion que se tomo en cada paso
	
	int* destinos_visitados;

	const int cant_destinos;
	const int cant_pociones;


public:
	int distancia;
	int paso;

	struct destino
	{
		int tipo;
		int cant_pociones;
		pair <int, int> posicion;
		destino(int tipo, int cant_pociones, pair <int, int> posicion): 
		tipo(tipo),
		cant_pociones(cant_pociones),
		posicion(posicion){};

	};
	struct Eleccion
	{
		int distancia, id; // El id da ordinalidad a todas las elecciones posibles, dentro de la matriz #personas x #personas
		bool posible;

		int tipo;
		int pocionesNecesarias;
		pair <int, int> posicion;
		const MaestroPokemon* MP;
		Eleccion(const MaestroPokemon* ash): 
		MP(ash),
		id(-1){
			recalcular();
		};

		Eleccion(){};

		void recalcular(){
			id = id + 1;

			posible = MP->cant_destinos<id && MP->destinos_visitados[id]==0;
			if (posible)
			{
				double x, y;
				if (id > MP->cant_gimnasios)
				{
					//Si es una poke parada
					tipo = PP;
					int id2 = id - MP->cant_gimnasios;
					posicion = MP->posiciones_pp[id2];
					
					x = pow(posicion.first - MP->eleccionActual.posicion.first, 2);
					y = pow(posicion.second - MP->eleccionActual.posicion.second, 2);
					pocionesNecesarias = 0;
				}else{
					//Si es un gym
					tipo = GIMNASIO;
					pair <pair <int,int>, int> gym = MP->gyms[id];
					pair<int, int> posDestino = gym.first;
					x = pow(posDestino.first - MP->eleccionActual.posicion.first, 2);
					y = pow(posDestino.second - MP->eleccionActual.posicion.second, 2);
					pocionesNecesarias = gym.second;
				}
				distancia = x + y;
				
			}
		}
	};


		MaestroPokemon(const int cant_gimnasios, const int cant_pokeParadas, const int * cap_mochila, const pair <pair <int,int>, int>* gyms, pair <int,int> posiciones_pp);
		~MaestroPokemon();
	//Devuelve el identificador de la eleccion
		Eleccion eleccionPosible();

		void elegir(const Eleccion eleccion);
		bool deshacerEleccion();
		bool gane();

	//Para ver el estado del sistema
		void printEleccion(Eleccion par) const;
		void printStatus()const;


	private:
		int cant_pokeParadas;
		int capacidad_mochila, cantidad_pociones;
		pair <pair <int,int>, int>* gyms;
		pair <int,int>* posiciones_pp;
		int cant_gimnasios;
		int cant_gimnasios_por_ganar;
		std::list<Eleccion> * decisiones;
		Eleccion eleccionActual;
		bool eleccionValida(Eleccion eleccion) const;



	};

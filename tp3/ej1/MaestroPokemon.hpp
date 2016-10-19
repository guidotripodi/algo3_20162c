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
		int distancia;
		int id = -1; // El id da ordinalidad a todas las elecciones posibles, dentro de la matriz #personas x #personas
		bool posible;

		int tipo =-1;
		int pocionesNecesarias = -1;
		pair <int, int> posicion;
		const MaestroPokemon* MP;
		Eleccion(){};
		Eleccion(const MaestroPokemon* MP):
		MP(MP),
		id(-1){
			recalcular();
		};

		

		void recalcular(){
			
			id = id + 1;

			posible = MP->cant_pokeParadas + MP->cant_gimnasios>id && MP->destinos_visitados[id]==0;
			if (posible)
			{
				double x, y;
				x = 0; y= 0;
				if (id >= MP->cant_gimnasios)
				{
					//Si es una poke parada
					tipo = PP;
					int id2 = id - MP->cant_gimnasios;
					
					posicion.first = MP->posiciones_pp[id2].first;
					//printf("QUE TIENE Y: %d \n", MP->posiciones_pp[id2].second);
					posicion.second = MP->posiciones_pp[id2].second;
					
					x = pow(posicion.first - MP->eleccionActual.posicion.first, 2);
					y = pow(posicion.second - MP->eleccionActual.posicion.second, 2);
					pocionesNecesarias = 0;
				}else{
					//Si es un gym
					tipo = GIMNASIO;
					posicion.first = MP->gyms[id].first.first;
					//printf("QUE TIENE Y: %d \n", MP->gyms[id].second);
					posicion.second = MP->gyms[id].first.second;
					
					x = pow(posicion.first - MP->eleccionActual.posicion.first, 2);
					y = pow(posicion.second - MP->eleccionActual.posicion.second, 2);
					pocionesNecesarias = MP->gyms[id].second;
				}
				printf("MP->eleccionActual->x %d ,MP->eleccionActual->y %d \n", MP->eleccionActual.posicion.first, MP->eleccionActual.posicion.second);
				printf("Pos nuevo destino %d ,Pos nuevo destino %d \n", posicion.first, posicion.second);
				printf("x %d ,y %d \n", x, y);
				distancia = x + y;

			}
		}
	};


		MaestroPokemon(int cant_gimnasios, int cant_pokeParadas, int cap_mochila, const pair <pair <int,int>, int> gyms[], const pair <int,int> posiciones_pp[]);
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
		 int capacidad_mochila;
		int cantidad_pociones;
		const pair <pair <int,int>, int>* gyms;
		const pair <int,int>* posiciones_pp;
		int cant_gimnasios;
		int cant_gimnasios_por_ganar;
		std::list<Eleccion> * decisiones;
		Eleccion eleccionActual;
		bool eleccionValida(Eleccion eleccion) const;



	};

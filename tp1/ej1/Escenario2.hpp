#include <list>
#include <algorithm>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Escenario2 {

private:
	//Guardo la eleccion que se tomo en cada paso
	const int LADO_A = 0;
	const int LADO_B = 1;



	int personas_totales;

	int * personas_ladoA;
	int cant_canibales_ladoA;
	int cant_arqueologos_ladoA;

	int cant_canibales_ladoB;
	int cant_arqueologos_ladoB;

	const int * tiempos_arqueologos;
	const int * tiempos_canibales; 


public:
	int tiempo;
	int tienenLampara;
	int paso;

	struct Persona
	{
		//El primer id es el idde persona
		int id, canibal, lado, tiempo;
		const Escenario2* escenario;

		void setId(int idPersona){
			id = idPersona;
			canibal = escenario->cant_arqueologos_ladoA + escenario->cant_arqueologos_ladoB <= idPersona;
			lado = !escenario->personas_ladoA[id];
			if (canibal)
			{
				int id_canibal_arq = id -escenario->cant_arqueologos_ladoA - escenario->cant_arqueologos_ladoB;
				tiempo = escenario->tiempos_canibales[id_canibal_arq];
			}else{
				tiempo = escenario->tiempos_arqueologos[id];
			}
		}

	};
	struct Eleccion
	{
		Persona primero, segundo;
		int tiempo, id; // El id da ordinalidad a todas las elecciones posibles, dentro de la matriz #personas x #personas
		bool posible;
		int cantCanibales, cantArqueologos;

		const Escenario2* escenario;
		Eleccion(){};
		Eleccion(const Escenario2* esc){
			id = 0;
			escenario = esc;
			primero.escenario = esc;
			segundo.escenario = esc;
			primero.setId(0);
			segundo.setId(0);
			tiempo = primero.tiempo;
			cantCanibales = primero.canibal;
			cantArqueologos = !primero.canibal;
			posible = id < (escenario->personas_totales * escenario->personas_totales);
			
		}

		void recalcular(){
			id = id + 1;
		//std::cout << "id 0: "<<id;
			//Obtengo idPersona
			int a = id / escenario->personas_totales;
			int b = id % escenario->personas_totales;

			//Veo si el valor de la tupla que forman es valido en la sucesion
			if (b<a)
			{
				id = a + a * (escenario->personas_totales);
				a = id / escenario->personas_totales;	
				b = id % escenario->personas_totales;
			}

			//std::cout << "--> id 1: "<<id<<"\n";
			
			primero.setId(a);
			segundo.setId(b);

			cantCanibales = primero.canibal;
			cantArqueologos = !primero.canibal;

			if (primero.id != segundo.id)
			{
				cantCanibales += segundo.canibal;
				cantArqueologos += !segundo.canibal;
			}

			//Es posible si el id representa a una combinacion de personas (combinatorio de personas)
			posible = id < (escenario->personas_totales * escenario->personas_totales);

		}


	};

	struct Nodo{
		Nodo *presente;
		Nodo *ausente;

		
	};

	struct HistoricoEstados {
		Escenario2* escenario;

		//Voy a guardar un trie en donde el alfabeto es 0 , 1: de esta forma puedo verificar si existioç
		//la combinacion en O(n)

		//Para implementarlo, al saber que va a ser un arbol con nodos de 2 posiciones y 2 aristas, lo mando a un array :)
		//
		Nodo* historia;

		HistoricoEstados(Escenario2* esc){
			escenario = esc;
			historia = new Nodo();
		}

		void marcarHistoria(Eleccion eleccion, int islaAEnviar){

			Nodo* node = historia;
			
			int idPersonaNodo = 0;

			while(idPersonaNodo < escenario->personas_totales){
				if (escenario->personas_ladoA[idPersonaNodo])
				{
					if (node->presente==NULL)
					{
						node->presente = new Nodo();
					}
					node = node->presente; 
				}else{
					if (node->ausente==NULL)
					{
						node->ausente = new Nodo();
					}
					node = node->ausente;
				}

				idPersonaNodo++;
			}

		}

		bool ocurrioEstado(Eleccion eleccion, int islaAEnviar){

			bool ocurrio = false;
			int idP1 = eleccion.primero.id;
			int idP2 = eleccion.segundo.id;
			Nodo* node = historia;
			
			int idPersonaNodo = 0;
			while(node!=NULL){
				if (idPersonaNodo!=idP1 && idPersonaNodo!=idP2)
				{
					if (escenario->personas_ladoA[idPersonaNodo])
					{
						node = node->presente; 
					}else{
						node = node->ausente;
					}
				}else{
				 	//Simulo que ya lo envie a dicha isla, en la historia tiene que estar como ya del otro lado
					if (islaAEnviar == 1)
					{
						node = node->presente;
					}else{
						node = node->ausente;
					}
				} 
				idPersonaNodo++;
			}
			if (idPersonaNodo == escenario->personas_totales)
			{
				ocurrio = true;
			}

			return ocurrio;
		}

		void borrarHistoria(Eleccion eleccion){

		}

	};


	Escenario2(const int cantA, const int cantC, const int * tiempos_arqueologos, const int * tiempos_canibales);
	~Escenario2();
	//Devuelve el identificador de la eleccion
	Eleccion envioPosible();
	Eleccion retornoPosible();

	void enviarEleccion(const Eleccion eleccion);
	void retornarEleccion(const Eleccion eleccion);
	bool deshacerEnvio();
	bool deshacerRetorno();
	int pasaronTodos();

	//Para ver el estado del sistema
	void printEleccion(Eleccion par) const;
	void printStatus()const;
	HistoricoEstados* historial;

private:

	std::list<Eleccion> * decisiones;
	Eleccion eleccionActual;
	bool envioValido(Eleccion eleccion) const;
	bool retornoValido(Eleccion eleccion) const;
	bool estaBalanceadoEnviandoEleccion(Eleccion eleccion) const;
	bool estaBalanceadoRetornandoEleccion(Eleccion eleccion) const;


};
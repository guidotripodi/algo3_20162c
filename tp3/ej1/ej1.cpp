//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "Escenario2.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

int main(int argc, char* argv[])
{
	int cant_arqueologos, cant_canibales;
	cin >> cant_arqueologos >> cant_canibales;


	int tiempos_arqueologos[cant_arqueologos];
	int tiempos_canibales[cant_canibales];

	int i = 0;
	for (i = 0; i < cant_arqueologos; i++)
	{
		cin >> tiempos_arqueologos[i];
	}
	for (i = 0; i < cant_canibales; i++)
	{
		cin >> tiempos_canibales[i];
	}

	int f = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	cout <<f<<"\n";
	
	return 0;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{
	bool exitoBackPar = true;
	bool exitoBackLampara = true;
	int sol = 0;
	int minimo = -1; 
	Escenario2 escenario = Escenario2(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	while(exitoBackLampara && exitoBackPar){
		if (escenario.pasaronTodos())
		{
			if (escenario.tiempo < minimo || minimo == -1)
			{
				minimo = escenario.tiempo;
			}
			sol++;
		}

		
		if (escenario.tienenLampara)
		{
			Escenario2::Eleccion eleccion = escenario.envioPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada
			if (eleccion.posible==1 && (minimo == -1 || escenario.tiempo<minimo))
			{
				escenario.enviarEleccion(eleccion);
			}else{
				//vuelve al paso anterior
				exitoBackLampara = escenario.deshacerRetorno();

			}
		}else{
			Escenario2::Eleccion eleccion = escenario.retornoPosible();

			//Si hay un farolero que pueda hacer que retorne y que me mantenga el tiempo menor al ya encontrado
			if (eleccion.posible==1 && (minimo == -1 || escenario.tiempo < minimo))
			{
				escenario.retornarEleccion(eleccion);

			}else{
				exitoBackPar = escenario.deshacerEnvio();

			}
		}

		
	}

	return minimo;
}

//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "Escenario2.hpp"
#define CANT_MAX 6

using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

int main(int argc, char* argv[])
{
	
	int cant_arqueologos, cant_canibales;
	int h,x;
	int tiempos_arqueologos[CANT_MAX];
	int tiempos_canibales[0];

	for(int i = 0; i < CANT_MAX; i++){
		tiempos_arqueologos[i] = i + 1;//no cuento el cero
		cant_arqueologos = i + 1;
		cant_canibales = 0;
		printf("Cantidad de arqueologos: %d, cantidad de canibales: %d \n",cant_arqueologos, cant_canibales );
		int t = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
		cout <<t<<"\n";
	}

	return 0;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{
	bool exitoBackPar = true;
	bool exitoBackLampara = true;
	int sol = 0;
	int minimo = -1; 
//	cout<<"Inicializando escenario...\n";
	Escenario2 escenario = Escenario2(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
//	cout<<"Escenario listo\n";
	//int i = 0;
	while(exitoBackLampara && exitoBackPar){
//		cout<<"----------------------------------------------\nNuevo paso:\n";
		escenario.printStatus();
		//De haber encontrado una solucion, obtengo el tiempo logrado
		//cout<<"tiempo: "<<escenario.tiempo<<"\n";
		if (escenario.pasaronTodos())
		{
			if (escenario.tiempo < minimo || minimo == -1)
			{
				minimo = escenario.tiempo;
			}
			sol++;
			//cout<<"||Fin de rama: logrado = "<<escenario.tiempo<<" minimo: "<<minimo<<" || \n";
		}

		
		if (escenario.tienenLampara)
		{
			Escenario2::Eleccion eleccion = escenario.envioPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada
			if (eleccion.posible==1 && (minimo == -1 || escenario.tiempo<minimo))
			{
				//cout<<"> Enviando ";
				escenario.printEleccion(eleccion);
				//cout<<"\n";

				escenario.enviarEleccion(eleccion);
			}else{
				//vuelve al paso anterior
			//	cout<<"> Backtracking a retorno\n";
				exitoBackLampara = escenario.deshacerRetorno();

			}
		}else{
			Escenario2::Eleccion eleccion = escenario.retornoPosible();

			//Si hay un farolero que pueda hacer que retorne y que me mantenga el tiempo menor al ya encontrado
			if (eleccion.posible==1 && (minimo == -1 || escenario.tiempo < minimo))
			{
				//cout<<"< Retornando eleccion ";
				escenario.printEleccion(eleccion);
				//cout<<"\n";
				escenario.retornarEleccion(eleccion);

			}else{
				//cout<<"< Backtracking a envio\n";
				exitoBackPar = escenario.deshacerEnvio();

			}
		}

		
	}

//	cout<<"Soluciones encontradas: "<<sol<<"\n";

	return minimo;
}

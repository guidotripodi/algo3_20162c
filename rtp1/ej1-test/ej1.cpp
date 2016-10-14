//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "Escenario2.hpp"
using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

int main(int argc, char* argv[])
{
	int cant_arqueologos, cant_canibales;

	int i,j,h,x;
	int tiempos_arqueologos[6];
	int tiempos_canibales[6];
	i = 0; j = 0;
	while(i + j <7){
		j = 0;
		while(i + j <7 && j<i){
			j++;
			x = 1;
			while(x < 2){
				cant_arqueologos = 3;
				cant_canibales = 3;
				h = 0;
				while(h < i){
					tiempos_arqueologos[h] = 1;
					h++;
				}
				h = 0;
				while(h < j){
					tiempos_canibales[h] = 1;
					h++;
				}
				printf("Cantidad de arqueologos: %d, cantidad de canibales: %d \n",cant_arqueologos, cant_canibales );
				int t = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
				cout <<t<<"\n";
				x++;
		}
				if (j+1 == i || j+1 + i == 7){
					break;
				}
	}
	if (j == 3){
		j = 0;
	}
	i++;
	}
	

	return 1;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{
	bool exitoBackPar = true;
	bool exitoBackLampara = true;
	int sol = 0;
	int minimo = -1; 
	Escenario2 escenario = Escenario2(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	while(exitoBackLampara && exitoBackPar){
		escenario.printStatus();
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
				escenario.printEleccion(eleccion);
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
				escenario.printEleccion(eleccion);
				escenario.retornarEleccion(eleccion);

			}else{
				exitoBackPar = escenario.deshacerEnvio();

			}
		}

		
	}


	return minimo;
}

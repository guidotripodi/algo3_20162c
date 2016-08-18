//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
using namespace std;



int main(int argc, char* argv[])
{
 	ifstream input( "ej1.in" );
 	int cant_arqueologos, cant_canibales;
 	input >> cant_arqueologos >> cant_canibales;
 	
 	int tiempos_arqueologos[cant_arqueologos];
 	int tiempos_canibales[cant_canibales];

 	int i = 0;
 	for (i = 0; i < cant_arqueologos; i++)
 	{
 		tiempos_arqueologos[i];
 	}
 	for (i = 0; i < cant_arqueologos; i++)
 	{
 		tiempos_canibales[i];
 	}

 	int t = algoritmoResolucion(cant_arqueologos, cant_canibales, &tiempos_arqueologos, &tiempos_canibales);
	
	cout << t;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{
	bool exitoBackPar = true;
	bool exitoBackLampara = true;
	bool minimo = -1;

	Escenario escenario = Escenario(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);

	while(exitoBackLampara || exitoBackPar){
		if (escenario.tienenLampara)//flag
		{
			par = escenario.parPosible();
			if (par>-1)//Busco en el casillero del paso si me quedan pares posibles
			{
				enviarPar(par);//flag + anotacion en arreglos + 1 paso más
			}else{
				exitoBackLampara = escenario.backtrackRetorno(farolero);//vuelve al paso anterior
			}
		}else{
			farolero = escenario.retornoPosible();
			if (farolero>-1)//busco en el casillero
			{
				retornarLampara(farolero);//flag + anotacion en arreglos + 1 paso más
			}else{
				 exitoBackPar = escenario.backtrackPar(par);//vuelve al paso anterior y cambia de rama
			}
		}

		if (escenario.pasaronTodos())
		{
			if (escenario.tiempo < minimo || minimo == -1)
			{
				minimo = escenario.tiempo;
			}
		}
	}

	return minimo;
}

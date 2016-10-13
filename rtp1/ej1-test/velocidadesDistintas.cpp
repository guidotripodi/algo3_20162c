#include <iostream>
#include <fstream>
#include "Escenario2.hpp"
#include <chrono>

#define ya chrono::high_resolution_clock::now
#define CANT_MAX 6

using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

int main(int argc, char* argv[])
{
	int cant_arqueologos, cant_canibales;
	int tiempos_arqueologos[CANT_MAX];
	int tiempos_canibales[CANT_MAX];

	for(int i = 1; i <= CANT_MAX; i++){
		for(int j = 0; (i + j) <= CANT_MAX; j++){
			if(i != 0) tiempos_arqueologos[i - 1] = i;
			
			cant_arqueologos = i;
			if( j <= i){
			cant_canibales = j;
			if(j != 0) tiempos_canibales[j - 1] = j;
			printf("Cantidad de arqueologos: %d, cantidad de canibales: %d \n",cant_arqueologos, cant_canibales );
			auto start = ya();
			int f = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
			auto end = ya();
			//cout <<f<<"\n";
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
			cout << "\n";
		}
		}
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
//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "Escenario.hpp"
using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

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
		input >> tiempos_arqueologos[i];
	}
	for (i = 0; i < cant_arqueologos; i++)
	{
		input >> tiempos_canibales[i];
	}
	cout<<"Entrada inicializada: comenzando algoritmo...\n";
	int t = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	
	cout << "Resultado: "<<t<<"\n";

	return 1;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{
	bool exitoBackPar = true;
	bool exitoBackLampara = true;
	int minimo = -1; 
	cout<<"Inicializando escenario...\n";
	Escenario escenario = Escenario(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	cout<<"Escenario listo\n";
	int i = 0;
	while(exitoBackLampara && exitoBackPar){

		//De haber encontrado una solucion, obtengo el tiempo logrado
		if (escenario.pasaronTodos())
		{
			if (escenario.tiempo < minimo || minimo == -1)
			{
				minimo = escenario.tiempo;
			}
			cout<<"Fin de rama: minimo logrado = "<<escenario.tiempo<<"\n";
		}

		exitoBackPar = true;
		exitoBackLampara = true;
		if (escenario.tienenLampara)
		{
			int par = escenario.parPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada
			if (par>-1 && (minimo == -1 || escenario.tiempo<minimo))
			{
				cout<<"Enviando ";
				escenario.printPar(par);
				cout<<"\n";

				escenario.enviarPar(par);
			}else{
				//vuelve al paso anterior
				cout<<"No se pudo enviar ningun par, aplicando backtracking a farolero\n";
				exitoBackLampara = escenario.backtrackFarolero();
				cout<<"Fin backtrack\n";
			}
		}else{
			int farolero = escenario.faroleroPosible();
			//cout<<"Farolero "<<farolero<<" evaluado como candidato\n";
			//Si hay un farolero que pueda hacer que retorne y que me mantenga el tiempo menor al ya encontrado
			
			if (farolero>-1 && (minimo == -1 || escenario.tiempo < minimo))
			{
				cout<<"Enviando como farolero a ";
				escenario.printPersona(farolero);
				cout<<"\n";
				escenario.enviarFarolero(farolero);
				//cout<<"Persona "<<farolero<<" enviada como farolero\n";
			}else{
				cout<<"No se pudo enviar ningun farolero, aplicando backtracking a par\n";
				exitoBackPar = escenario.backtrackPar();
				cout<<"Fin backtrack\n";
				//cout<<"Resultado backtrack de par: "<<exitoBackPar<<"\n";
			}
		}

		
	}

	return minimo;
}

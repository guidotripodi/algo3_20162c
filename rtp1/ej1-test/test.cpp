//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "trie.cpp"
#include <string> 
using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales);

int main(int argc, char* argv[])
{
	//ifstream input( "ej1.in" );
	//ifstream input = stdin;
/*	int cant_arqueologos, cant_canibales;
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
//	cout<<"Entrada inicializada: comenzando algoritmo...\n";
	int t = algoritmoResolucion(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);*/
	
	//cout <<t<<"\n";
	
	TrieTree t;

	char a[] = "hola";
	t.insert(a,0);
	vector<char> v;
	t.lexicographPrint(t.root,v);
	t.removeWord(t.root,a);
	t.lexicographPrint(t.root,v);
	t.insert(a,0);
	t.lexicographPrint(t.root,v);
	return 1;
}

int algoritmoResolucion(int cant_arqueologos, int cant_canibales, int * tiempos_arqueologos, int * tiempos_canibales)
{

//	cout<<"Inicializando escenario...\n";
	//Escenario2 escenario = Escenario2(cant_arqueologos, cant_canibales, tiempos_arqueologos, tiempos_canibales);
	//escenario.printStatus();
//	cout<<"Escenario listo\n";
	
/*
	cout<<"1 - Calculando envio...\n";
	Escenario2::Eleccion eleccion = escenario.envioPosible();
	escenario.printEleccion(eleccion);
	cout<<"Enviando... \n";
	escenario.enviarEleccion(eleccion);
	cout<<"Revisando historia...\n";
	cout<<"Ocurrio:"<<escenario.historial->ocurrioEstado(eleccion, 1)<<'\n';

	cout<<"2 - Calculando envio...\n";
	Escenario2::Eleccion eleccion2 = escenario.retornoPosible();
	escenario.printEleccion(eleccion2);
	cout<<"Retornando... \n";
	escenario.retornarEleccion(eleccion2);
	cout<<"Revisando historia...\n";
	cout<<"Ocurrio:"<<escenario.historial->ocurrioEstado(eleccion2, 1)<<'\n';
	escenario.printStatus();

	cout<<"3 - Calculando envio...\n";
	Escenario2::Eleccion eleccion3 = escenario.envioPosible();
	escenario.printEleccion(eleccion3);
	cout<<"Enviando... \n";
	escenario.enviarEleccion(eleccion3);
	cout<<"Revisando historia...\n";
	cout<<"Ocurrio:"<<escenario.historial->ocurrioEstado(eleccion3, 1)<<'\n';
	escenario.printStatus();

	

	/*
	cout<<"Retornando\n";
	eleccion = escenario.retornoPosible();
	//escenario.printEleccion(eleccion);
	escenario.retornarEleccion(eleccion);
	escenario.printStatus();

	cout<<"Enviando\n";
	eleccion = escenario.envioPosible();
	//escenario.printEleccion(eleccion);
	escenario.enviarEleccion(eleccion);
	escenario.printStatus();*/



	return 1;
}

//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include "Escenario2.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
#define CANT_MAX 10

using namespace std;


int main(int argc, char* argv[])
{
	int x = 7;

	for(int i = 1; i < x; i++){
		long long complejidad = pow(i,pow(2,i+1));
			auto start = ya();
			complejidad = complejidad*complejidad*15;
		for (long long h = 0; h < complejidad; ++h){
			//printf("h: %lld\n", h);
			
			long long array[complejidad];
			for(long long j = 0; j < i; j++){
				long long array1[complejidad];
				long long saraza = 1000;
				if (saraza == 1000) {
					saraza = saraza*saraza;
				}
				if (j < i && j > 3){
					saraza = saraza*saraza;
				}
				if (j < i && j < 3 ){
					saraza = saraza*j*saraza;
				}

		
			}
		}	
			auto end = ya();
			//cout <<f<<"\n";
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
			cout << "\n";
	}
	

	return 0;
}

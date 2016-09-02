#include "balanza.h"
#include "tests.cpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>

int main(int argc, char* argv[]){
	
	if(argc > 1){
		if(strcmp(argv[1], "test") == 0){
			//tests
			test3i();
			testPSumaDePotencias();
			testPnumerosPares();
			testPnumerosImpares();
			test_random();
		} else{
			printf("Modo de uso:\n");
			printf("	./ej2 (Toma la entrada por stdin)\n");
			printf("	./ej2 test (Corre las funciones de test)\n");
		}
	} else{
		//toma un valor de stdin y lo procesa
		std::string entrada;
		int peso;
		while( getline(std::cin, entrada) ){
			std::stringstream(entrada) >> peso;
		}
		FILE* file = stdout;
		Balanza b1(peso);
		b1.imprimir(file);
	}

	return 0;
}

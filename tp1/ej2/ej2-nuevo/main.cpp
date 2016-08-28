//#include "ejercicio2.cpp"
#include "balanza.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>

int main(int argc, char* argv[]){
	
	if(argc > 1){
		if(strcmp(argv[1], "test") == 0){
			//tests
		} else{
			printf("Bad input\n");
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

//#include "ejercicio2.cpp"
#include "balanza.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

int main(){

	std::string entrada;
	int peso;
	while( getline(std::cin, entrada) ){
		std::stringstream(entrada) >> peso;
	}

	FILE* file = stdout;
	Balanza b1(peso);
	b1.imprimir(file);

	return 0;
}

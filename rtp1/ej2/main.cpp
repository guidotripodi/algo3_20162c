#include "balanza.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>

int main(int argc, char* argv[]){
	
		int peso;
		FILE* file = stdout;

		std::cin >> peso;

		Balanza b1(peso);
		b1.imprimir(file);

	return 0;
}

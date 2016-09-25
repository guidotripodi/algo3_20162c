#include "balanza.h"
#include "tests.cpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

int main(int argc, char* argv[]){
	
	if(argc > 1){
		if(strcmp(argv[1], "test") == 0){
			//tests
			test3i();
			testPSumaDePotencias();
			testPnumerosMultiplosDe3();
			testPnumerosNoMultiplosDe3();
			test_random();
		} else{
			printf("Modo de uso:\n");
			printf("	./ej2 (Toma la entrada por stdin)\n");
			printf("	./ej2 test (Corre las funciones de test)\n");
		}
	} else{
		//toma un valor de stdin y lo procesa
		//int peso;
		/*
		std::string entrada;
		while( getline(std::cin, entrada) ){
			std::stringstream(entrada) >> peso;
		}
		*//*
		FILE* file = stdout;

		std::cin >> peso;

		Balanza b1(peso);
		b1.imprimir(file);*/
	long long peso = 0;
	int i = 0;
	while(i < 1000){
			peso = i;
		if(peso % 3 == 1 || peso % 3 == 2){
			peso = i;
		 auto start = ya();
			Balanza b1(peso);
		auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
            printf("\n");
		
		}
		i++;
	}



		//Balanza b1(peso);
		//b1.imprimir(archivo);
		
	

		/* 
		 long long array[peso];
		 for (long long h = 0; h < peso; ++h)	{
		 		array[h] = peso;
		 	}
		 for (int x = 0; x < peso; ++x) {
		 	for (int h = 0; h < peso; ++h)	{
		 		if (array[h] == peso) {
		 			array[h] = peso * peso * array[h];
		 		}
		 		if (array[h] == peso * peso * array[h])	{
		 			array[h] = peso;
		 		}
		 			j = j+1;
		 	}
		 }*/
		//b1.imprimirPantalla();
	//	i++;


	}

	return 0;
}

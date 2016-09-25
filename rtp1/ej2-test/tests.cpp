//#include <chrono>

//#define ya chrono::high_resolution_clock::now
void test3i(){
	/*Caso P = 3^i*/
	FILE* archivo = fopen("./test3i.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 30){
		peso = pow(3,i);
		Balanza b1(peso);
		b1.imprimir(archivo);
		i++;
	}
}

void testPSumaDePotencias(){

	/*Caso P = 3^i + i-1 hasta i = 0*/
	FILE* archivo = fopen("./testSumaPotencias.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	int x = 0;
	while(i < 30){
		x = 0;
		while(x <= i){
			peso = peso + pow(3,x);
			x++;
		}
		Balanza b1(peso);
		b1.imprimir(archivo);
		i++;
	}
}

void testPnumerosMultiplosDe3(){

	/*Caso P = par*/
	FILE* archivo = fopen("./testNumerosMultpDe3.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 1000){
			peso = i;
		if(peso % 3 == 0){
			peso = i;
			Balanza b1(peso);
			b1.imprimir(archivo);
		}
		i++;
	}
}


void testPnumerosNoMultiplosDe3(){

	/*Caso P = par*/
	FILE* archivo = fopen("./testNumerosImpares.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 1000){
			peso = i;
		if(peso % 3 == 1 || peso % 3 == 2){
			peso = i;
			Balanza b1(peso);
			b1.imprimir(archivo);
		}
		i++;
	}
}


void test_random(){

	/*Caso P = par*/
	FILE* archivo = fopen("./tests.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 500){
		peso = i;	
		Balanza b1(peso);
		b1.imprimir(archivo);
		i++;
	}
}


/*TEST MEJOR CASO*/

void mejorcaso(){
		long long peso = 0;
	int i = 0;
	while(i < 30){
		peso = pow(3,i);
		// auto start = ya();
		Balanza b1(peso);
		//auto end = ya();
         //   cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
          //  printf("\n");
		//b1.imprimirPantalla();
		i++;
	}
}

/*TEST PEOR CASO */

void peorCaso(){

	/*Caso P = 3^i + i-1 hasta i = 0*/
	
	long long peso = 0;
	int i = 0;
	int x = 0;
	while(i < 30){
		x = 0;
		while(x <= i){
			peso = peso + pow(3,x);
			x++;
		}
		// auto start = ya();
		Balanza b1(peso);
		//auto end = ya();
         //   cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
          //  printf("\n");
		i++;
	}
}

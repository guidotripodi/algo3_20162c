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
			peso = pow(3,x);
			x++;
		}
		Balanza b1(peso);
		b1.imprimir(archivo);
		i++;
	}
}

void testPnumerosPares(){

	/*Caso P = par*/
	FILE* archivo = fopen("./testNumerosPares.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 500){
			peso = i;
		if(peso % 2 == 0){
			peso = i;
			Balanza b1(peso);
			b1.imprimir(archivo);
		}
		i++;
	}
}


void testPnumerosImpares(){

	/*Caso P = par*/
	FILE* archivo = fopen("./testNumerosImpares.txt", "a");
	//FILE* archivo = stdout;
	long long peso = 0;
	int i = 0;
	while(i < 500){
			peso = i;
		if(peso % 2 == 1){
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

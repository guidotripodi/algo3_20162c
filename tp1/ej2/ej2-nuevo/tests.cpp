void test3i(){

	/*Caso P = 3^i*/
	long long peso = 0;
	int i = 0;
	while(i < 30){
		peso = pow(3,i);
		Balanza b1(peso);
		b1.imprimir(stdout);
		i++;
	}
}

void testPSumaDePotencias(){

	/*Caso P = 3^i + i-1 hasta i = 0*/
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
		b1.imprimir(stdout);
		i++;
	}
}

void testPnumerosPares(){

	/*Caso P = par*/
	long long peso = 0;
	int i = 0;
	while(i < 500){
			peso = i;
		if(peso % 2 == 0){
			peso = i;
			Balanza b1(peso);
			b1.imprimir(stdout);
		}
		i++;
	}
}


void testPnumerosImpares(){

	/*Caso P = par*/
	long long peso = 0;
	int i = 0;
	while(i < 500){
			peso = i;
		if(peso % 2 == 1){
			peso = i;
			Balanza b1(peso);
			b1.imprimir(stdout);
		}
		i++;
	}
}


void test_random(){

	/*Caso P = par*/
	long long peso = 0;
	int i = 0;
	while(i < 500){
		peso = i;	
		Balanza b1(peso);
		b1.imprimir(stdout);
		i++;
	}
}
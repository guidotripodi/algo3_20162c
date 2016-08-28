#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "balanza.h"
//con el mismo razonamiento que en la demo las pesas usadas son siempre menos que raiz de P

int main(){ 
    long long  pesa = 14;

//ejemplo	
	FILE* file = stdout;
	Balanza b1(pesa); //creacion de balanza, resuelve problema
	b1.imprimir(file);

/*	
	while (i > 0) {
        //pesa = pow(10,i); 
        pesa = i; 
        printf("pesa : %lld \n", pesa);
        balancear(pesa);
        i--;
    }
*/    
	return 0;
}

#include <stdio.h>
#include <math.h>
//con el mismo razonamiento que en la demo las pesas usadas son siempre menos que raiz de P

void balancear(int p){
	int equilibrioActual = p;
	// La primera potencia mayor que p
	int i = 0;
	while( pow(3, i) < p ) i++;
	
	int cantidadPesas = (int) sqrt(p) + 1;
	int pesasUtilizadas[cantidadPesas]; //array vacio de pesas
	int j = 0; //itera el array de pesas utilizadas
	bool estaEnNegativo = false;
	int pesaActual = pow(3, i);
	int n = equilibrioActual - pesaActual;
	for( bool terminar = false; !terminar; ){
		switch(n){
			case 0:
				pesasUtilizadas[j] = pesaActual;
				j++;
				terminar = true;
				break;
			case 1:
				pesasUtilizadas[j] = pesaActual;
				pesasUtilizadas[j+1] = 1; //pow(3, 0)
				terminar = true;
				break;
			default:
				break;
			}//probablemente no ande y lo tenga que hacer con if else
		if(n > 1){//TODO modulo
		
		}
	}
} 

#include <stdio.h>
#include <stdlib.h> // abs (modulo)
#include <math.h> // sqrt y potencia
#include "balanza.h"
//con el mismo razonamiento que en la demo las pesas usadas son siempre menos que raiz de P

//crea una balanza, en lo posible inmutable
//Al crearse resuelve el problema
Balanza::Balanza(int p){
	peso_llave = p;
	cant_pesas = (int) sqrt(peso_llave) + 1; // valor tentativo
	pesasUtilizadas = new int[cant_pesas];
	platoIzquierdo = new int[cant_pesas];
	platoDerecho = new int[cant_pesas];
	size_izq = 0;
	size_der = 0;
	balancear();
}


void Balanza::balancear(){
	int equilibrioActual = peso_llave;
	// La primera potencia mayor que p
	int i = 0;
	while( pow(3,i) < peso_llave ) i++;
	
	int j = 0; //itera el array de pesas utilizadas
	bool estaEnNegativo = false;
	int pesaActual = pow(3, i);
	int n = equilibrioActual - pesaActual;
	for( bool terminar = false; !terminar; ){
		if( n == 0 ){
			pesasUtilizadas[j] = pesaActual;
			terminar = true;
			//cant_pesas = j;
		} else if( abs(n) == 1 ){
			pesasUtilizadas[j] = pesaActual;
			pesasUtilizadas[j+1] = 1; //pow(3, 0)
			//cant_pesas = j+1;
			terminar = true;
		} else if( abs(n) > 1 && abs(n) < equilibrioActual ){
			pesasUtilizadas[j] = pesaActual;
			i--;
			//equilibrioActual = n;
			estaEnNegativo = n < 0; //se setea true si n menor 0
			equilibrioActual = abs(n);
		} else if( abs(n) >= equilibrioActual ){
			i--;
		}
		if( estaEnNegativo ){
			pesaActual = pow(3,i) * -1;
			pesaUno = pow(3,0) * -1; //TODO declarar esta variable
		} else{
			pesaActual = pow(3, i);
			pesaUno = pow(3, 0);
		}
		n = equilibrioActual - pesaActual;
	}
	armadoBalanza();
}

void Balanza::armadoBalanza(){//O(sqrt(p))
	int x = 0;
	int i = 0;
	int j = 0;
	while(x < cant_pesas){//pesasUtilizadas.size
		if( pesasUtilizadas[x] < 0 ){
			platoDerecho[i] = pesasUtilizadas[x] * -1;
			i++;
		} else{
			platoIzquierdo[j] = pesasUtilizadas[x];
			j++;
		}
		x++;
	}
	size_izq = j;
	size_der = i;
	invertir(platoDerecho, size_der);
	invertir(platoIzquierdo, size_izq);
}

void Balanza::invertir(int* arreglo, int size){
	int *otro = new int[size];
	for(int i = 0; i < size ; i++){
		otro[size - i] = arreglo[i];
	}
}

#include <stdio.h>
#include <math.h>
#include "balanza.h"
//con el mismo razonamiento que en la demo las pesas usadas son siempre menos que raiz de P


void Balanza::balancear(){
	int equilibrioActual = peso_llave;
	// La primera potencia mayor que p
	int i = 0;
	while( pow(3,i) < peso_llave ) i++;
	
	//TODO trasladar a metodo constructor
	//int cantidadPesas = (int) sqrt(peso_llave) + 1;
	//int pesasUtilizadas[cantidadPesas]; //array vacio de pesas
	int j = 0; //itera el array de pesas utilizadas
	bool estaEnNegativo = false;
	int pesaActual = pow(3, i);
	int n = equilibrioActual - pesaActual;
	for( bool terminar = false; !terminar; ){
		if( n == 0 ){
			pesasUtilizadas[j] = pesaActual;
			terminar = true;
		} else if( abs(n) == 1 ){
			pesasUtilizadas[j] = pesaActual;
			pesasUtilizadas[j+1] = 1; //pow(3, 0)
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
	//devolver(armadoBalanza);
}

void Balanza::armadoBalanza(){//O(sqrt(p))
	int x = 0;
	while(x < cant_pesas){//pesasUtilizadas.size
		if( pesasUtilizadas[x] < 0 ){
			platoDerecho[i] = pesasUtilizadas[x] * -1;
		} else{
			platoIzquierdo[j] = pesasUtilizadas[x];
		}
		x++;
	}
	invertir(platoDerecho);
	invertir(platoIzquierdo);
}

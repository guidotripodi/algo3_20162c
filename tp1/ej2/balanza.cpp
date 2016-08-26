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

Balanza::~Balanza(){
	delete[] pesasUtilizadas;
	delete[] platoDerecho;
	delete[] platoIzquierdo;
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
	int pesaUno = 1;
	for( bool terminar = false; !terminar; ){
		if( n == 0 ){
			pesasUtilizadas[j] = pesaActual;
			terminar = true;
			cant_pesas = j+1;
		} else if( abs(n) == 1 ){
			pesasUtilizadas[j] = pesaActual;
			if( n < 0 ){
				pesasUtilizadas[j+1] = pesaUno * -1;
			} else{
				pesasUtilizadas[j+1] = pesaUno;
			}
			cant_pesas = j+2;
			terminar = true;
		} else if( abs(n) > 1 && abs(n) < equilibrioActual ){
			//agrego una pesa y sigo loopeando
			pesasUtilizadas[j] = pesaActual;
			j++;
			i--;
			equilibrioActual = n;
			estaEnNegativo = n < 0; //se setea true si n menor 0
			equilibrioActual = abs(n);
		} else if( abs(n) >= equilibrioActual ){
			//La pesa que trate de usar es muy grande
			i--;
		}
		if( estaEnNegativo ){
			pesaActual = pow(3,i) * -1;
			pesaUno = pow(3,0) * -1; 
		} else{
			pesaActual = pow(3, i);
			pesaUno = pow(3, 0);
		}
		n = abs(equilibrioActual) - abs(pesaActual);
	}
	armadoBalanza();
}

void Balanza::armadoBalanza(){//O(sqrt(p))
	int x = 0;
	int i = 0;
	int j = 0;
	while( x < cant_pesas ){//pesasUtilizadas.size
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
	if( size < 2 ) return;
	int temp; 
	for( int i = 0; i < size/2 ; i++ ){
		temp = arreglo[i];
		arreglo[i] = arreglo[size - i - 1];
		arreglo[size - i - 1] = temp;
	}
}

void Balanza::imprimir(){
	printf("%d %d\n",this->size_izq, this->size_der);
	for( int i = 0; i < size_izq; i++ ){
		printf("%d ", platoIzquierdo[i]);
	}
	printf("\n");
	for( int j = 0; j < size_der; j++ ){
		printf("%d ", platoDerecho[j]);
	}
	printf("\n");
}

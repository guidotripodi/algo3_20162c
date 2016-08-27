#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//con el mismo razonamiento que en la demo las pesas usadas son siempre menos que raiz de P

void balancear(int p){
    
	int equilibrioActual = p;
	// obtengo la ultima suma parcial junto con el exponente de la ultima potencia
    int i = 0;
    int sumaParcial = 0;
    while( sumaParcial < p ) {
        sumaParcial+= pow(3,i);
        i++;
    };
    
    int size = i+1; // mas uno para el 0
    
    int sumasParciales[size];
    
    // armo el arreglo de sumas parciales
    while (i >= 0) {
        sumasParciales[i] = sumaParcial;
        sumaParcial=(sumaParcial-pow(3,i-1)); // -1 porque el exponente termina en +1 en el while anterior
        i--;
    }
    
    int middle = (size)/2;
    
    while (abs(equilibrioActual) > 0) {
        if (sumasParciales[middle] >= abs(equilibrioActual) && sumasParciales[middle-1] < abs(equilibrioActual)) {
        
            int potencia = sumasParciales[middle]-sumasParciales[middle-1];
            if (equilibrioActual < 0) {
                equilibrioActual = potencia + equilibrioActual;
                printf("plato derecho %d \n", potencia);
            }else {
                equilibrioActual = equilibrioActual - potencia;
                printf("plato izquierdo %d \n", potencia);
            }
            
            // me voy al intervalo mas chico
            size = middle;
            middle = middle/2;
        }else if (sumasParciales[middle] < abs(equilibrioActual)) {
            // estoy muy adentro, voy mas afuera
            middle = (middle+(size))/2;
        }else if (sumasParciales[middle-1] >= abs(equilibrioActual)) {
            // estoy muy afuera, voy mas adentro
            size = middle;
            middle = (middle)/2;
        }
    }
}


int main(){
    int i = 53;
    while (i > 0) {
        printf("pesa : %d \n", i);
        balancear(i);
        i--;
    }
    
	return 0;
}

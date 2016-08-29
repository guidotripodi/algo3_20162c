 #include "balanza.h"

Balanza::Balanza(int peso){
	p = peso;
	cant_pesas = (int) sqrt(p) + 1; // valor tentativo
	platoIzquierdo = new long long[cant_pesas];
	platoDerecho = new long long[cant_pesas];
	sizeIzq = 0;
	sizeDer = 0;
	balancear();
}

Balanza::~Balanza(){
	delete[] platoDerecho;
	delete[] platoIzquierdo;
}

//void Balanza::imprimir(long long* derecho, long long* izquierdo, int sizeDer, int sizeIzq){

void Balanza::imprimir(FILE* doc){
	fprintf(doc, "%lld %lld \n",sizeIzq, sizeDer);
	for( int i = 0; i < sizeIzq; i++ ){
		fprintf(doc, "%lld ", platoIzquierdo[i]);
	}
	fprintf(doc, "\n");
	for( int j = 0; j < sizeDer; j++ ){
		fprintf(doc, "%lld ", platoDerecho[j]);
	}
	fprintf(doc, "\n");
}

void Balanza::invertir(long long* arreglo, int size){
	if( size < 2 ) return;
	long long temp; 
	for( int i = 0; i < size/2 ; i++ ){
		temp = arreglo[i];
		arreglo[i] = arreglo[size - i - 1];
		arreglo[size - i - 1] = temp;
	}
}

void Balanza::balancear(){
    
	long long  equilibrioActual = p;
	// obtengo la ultima suma parcial junto con el exponente de la ultima potencia
    long long  i = 0;
    long long  sumaParcial = 0;
    while( sumaParcial < p ) {
        sumaParcial+= pow(3,i);
        i++;
    };
    
    long long  size = i+1; // mas uno para el 0
    
    long long  sumasParciales[size];
    
    // armo el arreglo de sumas parciales
    while (i >= 0) {
        sumasParciales[i] = sumaParcial;
		// -1 porque el exponente termina en +1 en el while anterior
        sumaParcial=(sumaParcial-pow(3,i-1));
        i--;
    }
    
    long long  middle = (size)/2;
	//long long platoDerecho[size];
	//long long platoIzquierdo[size];
	int j = 0;
	int k = 0;

    while (llabs(equilibrioActual) > 0) {
        if (sumasParciales[middle] >= llabs(equilibrioActual) &&
				sumasParciales[middle-1] < llabs(equilibrioActual)) {

            long long  potencia = sumasParciales[middle]-sumasParciales[middle-1];
            if (equilibrioActual < 0) {
                equilibrioActual = potencia + equilibrioActual;
                platoDerecho[j] = potencia;
				j++;
				//printf("plato derecho %lld \n", potencia);
            }else {
                equilibrioActual = equilibrioActual - potencia;
				platoIzquierdo[k] = potencia;
				k++;
                //printf("plato izquierdo %lld \n", potencia);
            }
            
            // me voy al intervalo mas chico
            size = middle;
            middle = middle/2;
        }else if (sumasParciales[middle] < llabs(equilibrioActual)) {
            // estoy muy adentro, voy mas afuera
            middle = (middle+(size))/2;
        }else if (sumasParciales[middle-1] >= llabs(equilibrioActual)) {
            // estoy muy afuera, voy mas adentro
            size = middle;
            middle = (middle)/2;
        }
    }
	sizeDer = j;
	sizeIzq = k;
	invertir(platoDerecho, sizeDer);
	invertir(platoIzquierdo, sizeIzq);
}


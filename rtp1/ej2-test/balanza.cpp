 #include "balanza.h"
 #include <list>

using namespace std;

Balanza::Balanza(long long peso){
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

void Balanza::imprimirPantalla(){
	printf("%lld %lld \n",sizeIzq, sizeDer);
	for( int i = 0; i < sizeIzq; i++ ){
		printf("%lld ", platoIzquierdo[i]);
	}
	printf("\n");
	for( int j = 0; j < sizeDer; j++ ){
		printf("%lld ", platoDerecho[j]);
	}
	printf("\n");
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

    list<long long> sumasParcialesList;
    
    // armo el arreglo de sumas parciales
    while (sumaParcial < p) {
        sumasParcialesList.push_back(sumaParcial);
		// -1 porque el exponente termina en +1 en el while anterior
        sumaParcial=(sumaParcial+pow(3,i));
        i++;
    }

    sumasParcialesList.push_back(sumaParcial);

    long long  sumasParciales[sumasParcialesList.size()];
	long long size = sumasParcialesList.size();
    i = 0;
    while(i < size){
    	sumasParciales[i] = sumasParcialesList.front();
		sumasParcialesList.pop_front();
    	i++;
    }

    long long  index = size-1;

	int j = 0;
	int k = 0;

    while (llabs(equilibrioActual) > 0) {
        if (sumasParciales[index] >= llabs(equilibrioActual) &&
				sumasParciales[index-1] < llabs(equilibrioActual)) {

            long long  potencia = sumasParciales[index]-sumasParciales[index-1];
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
        }
        
        index = index-1;
    }
	sizeDer = j;
	sizeIzq = k;
	invertir(platoDerecho, sizeDer);
	invertir(platoIzquierdo, sizeIzq);
}


#include <math.h>
#include <stdio.h>
#include <stdlib.h> // abs (modulo)

class Balanza{
	public:
		Balanza(long long p); 
		~Balanza();
		void imprimir(FILE*);
		void imprimirPantalla();
		//puedo imprimir por consola o a un archivo
	
	private:
		//void armadoBalanza();
		void balancear();
		long long p;
		
		void invertir(long long* arreglo, int size);
		long long cant_pesas;
		long long *platoDerecho;
		long long  *platoIzquierdo;
		long long sizeDer;
		long long sizeIzq;

};

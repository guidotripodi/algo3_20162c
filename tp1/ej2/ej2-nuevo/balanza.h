#include <math.h>
#include <stdio.h>
#include <stdlib.h> // abs (modulo)

class Balanza{
	public:
		//inicializacion es O(sqrt(p)) si no es todo una mentira
		Balanza(int p); 
		~Balanza();
		void imprimir(FILE*); 
		//puedo imprimir por consola o a un archivo
	
	private:
		//void armadoBalanza();
		void balancear();
		int p;
		
		void invertir(long long* arreglo, int size);
		int cant_pesas;
		long long *platoDerecho;
		long long  *platoIzquierdo;
		int sizeDer;
		int sizeIzq;

};

#include <math.h>
#include <stdio.h>

class Balanza{
	public:
		//inicializacion es O(sqrt(p)) si no es todo una mentira
		Balanza(int p); 
		~Balanza();
		void imprimir(); //o recargo el operador?	
	
	private:
		void armadoBalanza();
		void balancear();
		int peso_llave;
		
		//arrays? necesita ser armado medio dinamico esto
		//en caso de hacerllo con arreglos normales de C
		//necesito las siguientes variables
		//tamaño varia con la llave
		
		void invertir(int* arreglo, int size);
		int cant_pesas;
		int *pesasUtilizadas;
		int *platoDerecho;
		int *platoIzquierdo;
		int size_der;
		int size_izq;

		//sino listas enlazadas con iteradores
		//mas bonito, pero bastante laburo
};

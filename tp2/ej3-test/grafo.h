#include <iostream>
#include <list>


struct Arista{
	int destino;
	int peso;
	Arista(int destination, int weight):      
		destino(destination),
		peso(weight) {}
};

class Grafo{
	public:
		Grafo(int* aristas, int cantNodos, int cantAristas);//recibe el vector de ints yaa parseados?
		~Grafo();
		std::list<Arista>* vecinos(int vertice);
		
	private:
		std::list<Arista>* adyacencia; //lista de vecinos
};

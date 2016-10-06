#include <iostream>
#include <list>


struct Arista{
	long destino;
	long peso;
	Arista(long destination, long weight):      
		destino(destination),
		peso(weight) {}
};

class Grafo{
	public:
		Grafo(long* aristas, long cantNodos, long cantAristas);
		~Grafo();
		std::list<Arista>* vecinos(long vertice);
		
	private:
		std::list<Arista>* adyacencia; //lista de vecinos
};

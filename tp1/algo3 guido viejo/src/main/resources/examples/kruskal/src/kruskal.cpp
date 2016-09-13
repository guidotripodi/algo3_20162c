#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

////////////////////////// CLASE Arista //////////////////////////

class Arista{
	private:
		unsigned int _nod1, _nod2;
		int _peso;
		
	public:
		Arista(unsigned int n1, unsigned int n2, int p) : _nod1(n1), _nod2(n2), _peso(p) {}
		int peso() const { return _peso; }
		unsigned int nodo1() const { return _nod1; }
		unsigned int nodo2() const { return _nod2; }
		
		bool operator<(const Arista &ar) const {
			if(peso() != ar.peso()) return peso() < ar.peso();
			if(nodo1() != ar.nodo1()) return nodo1() < ar.nodo1();
			return nodo2() < ar.nodo2();
		}

};

typedef vector<Arista> Varist;

// Esta funcion podria quitarse luego
std::ostream &operator<<(std::ostream &stream, const Arista& ar){
	std::stringstream output;
	output << "[(" << ar.nodo1() << "," << ar.nodo2() << ") " << ar.peso() << "]";
	stream << output.str();
	return stream;
}

// Esta funcion es solo para testeo, podria quitarse luego
bool hayArista(const Varist& ars, unsigned int nod1, unsigned int nod2, int peso){
	bool ret = false;
	for(auto a : ars)
		if(a.peso() == peso)
			if((a.nodo1() == nod1 && a.nodo2() == nod2) || (a.nodo1() == nod2 && a.nodo2() == nod1)){
				ret = true; break; 
			}
	
	return ret;
}

////////////////////////// CLASE Adyacencia //////////////////////////

class Adyacencia{
	private:
		unsigned int _nod;
		int _peso;
		
	public:
		Adyacencia(unsigned int nod, int p) : _nod(nod), _peso(p) {}
		int peso() const { return _peso; }
		unsigned int nodo() const { return _nod; }
};

typedef vector<Adyacencia> Vady;

////////////////////////// CLASE UnionFind //////////////////////////

class UnionFind{
	// COMPLETAR !
	private:
		vector<unsigned int> _parent, _rank;
		
	public:
		UnionFind(unsigned int n){
			// Crea un bosque de n nodos. 
			// Cada nodo tiene rank 0 al principio. 
			// Cada nodo es su propio padre el principio. 
		}
		
		unsigned int findSet(unsigned int i){ 
			// Si el padre es el mismo nodo, devuelvo ese nodo. 
			// Si no, llamo recursivamente hacia el padre, y actualizo el padre del nodo. 
		}
		
		bool isSameSet(unsigned int i, unsigned int j){
			// Devuelve si 2 nodos pertenecen o no al mismo conjunto. 
		}
		
		void unionSet(unsigned int i, unsigned int j){
			// Si no pertenecen ya al mismo conjunto, los uno. 
			// El que tenga menor rank pasara a formar parte del que tenga mayor rank. 
			// Si ambos tienen igual rank es lo mismo cual uno a cual, pero debo aumentar el rank del que sea el padre. 
		}
};

////////////////////////// CLASE GrafoListaAdy //////////////////////////

class GrafoListaAdy{
	private:
		vector<Vady> _graf;
		unsigned int _nodos, _aristas;
	
	public:
		// O(n)
		GrafoListaAdy(int n){
			_graf = vector<Vady>(n);
			_nodos = n;
			_aristas = 0;
		}
		
		// O(n + m)
		GrafoListaAdy(int n, const Varist& aristas){
			_graf = vector<Vady>(n);
			_nodos = n;
			_aristas = 0;
			for(auto a : aristas){
				agregarAristaRapida(a);
			}
		}
		
		// O(1) --- Toma una arista
		void agregarAristaRapida(const Arista& ars){
			Adyacencia ady1 = Adyacencia(ars.nodo1(), ars.peso());
			Adyacencia ady2 = Adyacencia(ars.nodo2(), ars.peso());
			
			_graf[ars.nodo1()].push_back(ady2);
			_graf[ars.nodo2()].push_back(ady1);
			
			_aristas++;
		}
		
		// O(1) --- Toma los datos de una arista
		void agregarAristaRapida(unsigned int nod1, unsigned int nod2, int p){
			Adyacencia ady1 = Adyacencia(nod1, p);
			Adyacencia ady2 = Adyacencia(nod2, p);
			
			_graf[nod1].push_back(ady2);
			_graf[nod2].push_back(ady1);
			
			_aristas++;
		}
		
		// O(sonAdyacentes)
		void agregarArista(const Arista& ars){
			if(!sonAdyacentes(ars.nodo1(), ars.nodo2()) && ars.nodo1() != ars.nodo2()){
				agregarAristaRapida(ars);
			}
		}
		
		// O(sonAdyacentes)
		void agregarArista(unsigned int nod1, unsigned int nod2, int p){
			if(!sonAdyacentes(nod1, nod2) && nod1 != nod2){
				agregarAristaRapida(nod1, nod2, p);
			}
		}
		
		// O(1)
		Vady adyacentes(unsigned int nod) const{
			return _graf[nod];
		}
		
		// O(1)
		unsigned int grado(unsigned int nod) const{
			return adyacentes(nod).size();
		}
		
		// O(min{d(nod1), d(nod2)})
		bool sonAdyacentes(unsigned int nod1, unsigned int nod2) const{
			bool ret = false;
			if(grado(nod1) < grado(nod2)){
				for(auto ad : adyacentes(nod1))
					if(ad.nodo() == nod2) { ret = true; break; }
			}else{
				for(auto ad : adyacentes(nod2))
					if(ad.nodo() == nod1) { ret = true; break; }
			}
			return ret;
		}
		
		// O(n + m)
		Varist aristas() const{
			Varist ret;
			for(auto& nodAdy : _graf){
				unsigned int nod = &nodAdy - &_graf[0];
				for(auto ad : nodAdy){
					if(ad.nodo() > nod){
						Arista ars = Arista(nod, ad.nodo(), ad.peso());
						ret.push_back(ars);
					}
				}
			}
			return ret;
		}
		
		// O(1)
		unsigned int cantNodos() const{
			return _nodos;
		}
		
		// O(1)
		unsigned int cantAristas() const{
			return _aristas;
		}
		
		// O(m.log(m))
		int kruskal() const{
			// COMPLETAR !
		}
};

////////////////////////// Tests //////////////////////////

void testGrafo(){
	GrafoListaAdy graf = GrafoListaAdy(5);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 0);
	graf.agregarArista(1, 0, 2);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 1);
	graf.agregarArista(2, 0, 0);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 2);
	graf.agregarArista(3, 0, 3);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 3);
	graf.agregarArista(0, 2, 4);		// Esta no deberia agregar
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 3);
	graf.agregarArista(2, 1, 1);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 4);
	graf.agregarArista(4, 1, 4);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 5);
	graf.agregarArista(4, 3, 5);
	assert(graf.cantNodos() == 5 && graf.cantAristas() == 6);
	
	assert(graf.cantNodos() == 5);
	assert(graf.cantAristas() == 6);
	
	assert(graf.grado(0) == 3);
	assert(graf.grado(1) == 3);
	assert(graf.grado(2) == 2);
	assert(graf.grado(3) == 2);
	assert(graf.grado(4) == 2);
	
	assert(graf.sonAdyacentes(0, 1));
	assert(graf.sonAdyacentes(0, 2));
	assert(graf.sonAdyacentes(0, 3));
	assert(!graf.sonAdyacentes(0, 4));
	assert(graf.sonAdyacentes(1, 2));
	assert(!graf.sonAdyacentes(1, 3));
	assert(graf.sonAdyacentes(1, 4));
	assert(!graf.sonAdyacentes(2, 3));
	assert(!graf.sonAdyacentes(2, 4));
	assert(graf.sonAdyacentes(3, 4));
	
	Varist aristas = graf.aristas();
	
	assert(graf.cantAristas() == aristas.size());		// Mismo cardinal
	
	for(auto a : aristas){ 									// Todas las de la lista estan en el grafo
		assert(graf.sonAdyacentes(a.nodo1(), a.nodo2()));
	}
		
	for(unsigned int i=0; i<graf.cantNodos(); i++){		// Todas las del grafo estan en la lista
		for(auto ad : graf.adyacentes(i)){
			assert(hayArista(aristas, i, ad.nodo(), ad.peso()));
			assert(hayArista(aristas, ad.nodo(), i, ad.peso()));
		}
	}
}

void testGrafoKruskal(){
	GrafoListaAdy graf1 = GrafoListaAdy(1);
	assert(graf1.kruskal() == 0);
	
	GrafoListaAdy graf2 = GrafoListaAdy(2);
	graf2.agregarArista(0, 1, 4);
	assert(graf2.kruskal() == 4);
	
	GrafoListaAdy graf3 = GrafoListaAdy(3);
	graf3.agregarArista(0, 1, 8);
	graf3.agregarArista(0, 2, 2);
	graf3.agregarArista(1, 2, 4);
	assert(graf3.kruskal() == 6);
	
	GrafoListaAdy graf4 = GrafoListaAdy(4);
	graf4.agregarArista(0, 1, 3);
	graf4.agregarArista(0, 2, 5);
	graf4.agregarArista(0, 3, 1);
	graf4.agregarArista(2, 1, 4);
	graf4.agregarArista(3, 1, 9);
	graf4.agregarArista(2, 3, 7);
	assert(graf4.kruskal() == 8);
	
	GrafoListaAdy graf5 = GrafoListaAdy(5);
	graf5.agregarArista(0, 1, 6);
	graf5.agregarArista(0, 2, 6);
	graf5.agregarArista(0, 3, 5);
	graf5.agregarArista(0, 4, 12);
	graf5.agregarArista(2, 1, 3);
	graf5.agregarArista(3, 1, 1);
	graf5.agregarArista(4, 1, 1);
	graf5.agregarArista(2, 3, 10);
	graf5.agregarArista(2, 4, 8);
	graf5.agregarArista(3, 4, 8);
	assert(graf5.kruskal() == 10);
	
	GrafoListaAdy graf6 = GrafoListaAdy(6);
	graf6.agregarArista(0, 1, 4);
	graf6.agregarArista(0, 2, 1);
	graf6.agregarArista(0, 3, 1);
	graf6.agregarArista(0, 4, 6);
	graf6.agregarArista(0, 5, -1);
	graf6.agregarArista(1, 2, 5);
	graf6.agregarArista(1, 3, 7);
	graf6.agregarArista(1, 4, 1);
	graf6.agregarArista(1, 5, 5);
	graf6.agregarArista(2, 3, 1);
	graf6.agregarArista(2, 4, 6);
	graf6.agregarArista(2, 5, -4);
	graf6.agregarArista(3, 4, 8);
	graf6.agregarArista(3, 5, 0);
	graf6.agregarArista(4, 5, 14);
	assert(graf6.kruskal() == 0);
}

////////////////////////// --- //////////////////////////

int main(){
	testGrafo();
	testGrafoKruskal();
	
	// --- Oreon --- 
	int T;
	cin >> T;
	while(T--){
		int n; 
		// Cantidad de ciudades. 
		cin >> n;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				int soldados;
				// Leo la cantidad de soldados para cada tunel. 
				cin >> soldados;
			}
		}
	}
	
	return 0;
}

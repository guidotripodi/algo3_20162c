#include "stdio.h"
#include "algorithm"
using namespace std;


class UF {
  int *id, cont, *size;
  public:
// inizializacion conjunto N de elementos
UF(int N) {
    cont = N; 
    id = new int[N];
    size = new int[N];
    for (int i = 0; i<N; i++){
    	id[i] = i;
    	size[i] = 1;
    }
}

~UF() { 
	delete[] id; 
	delete[] size; 
}

// devuelve padre//representante
int find(int p) {
    int root = p;
    while (root != id[root]){
	    root = id[root];
	   }
    while (p != root) { 
    	int newp = id[p]; 
    	id[p] = root;
    	p = newp; 
    }
    return root;
}
// Concatenacion.
void unir(int x, int y) {
    int i = find(x);
    int j = find(y); 
    if (i == j) return;
    // concatenacion de conjuntos menor a mayor
    if (size[i] < size[j]) {
    	 id[i] = j;
    	 size[j] += size[i]; 
    }else{
    	id[j] = i;
    	size[i] += size[j]; 
    }
    cont--;
}
// chequeo padre
bool connected(int x, int y) { return find(x) == find(y); }
// devuelvo cantidad de conjuntos que van quedando 
int count() { return cont; }
};
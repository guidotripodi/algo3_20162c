#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int F, C;
int V, E;

int *altura;
int *padre;
int *costCompLider;
int *cantAristas;

struct Arista {
    int inicio;
    int fin;
    int costo;
    
    //si se quiere probar con monticulo entonces cambiar la desigualdad por > en las comparaciones
    bool operator<(const Arista &a) const
    {
        if (costo != a.costo)
            return costo < a.costo;
        if (inicio != a.inicio)
            return inicio < a.inicio;
        return fin < a.fin;
    }
};

struct Node {
    int i;
    int j;
    int value;
    bool visited;
    
    Node(): i(0),
    j(0),
    value((int)'#'),
    visited(false){}
};

Node*** Map; // Matriz mapa con Nodos

bool comparePtrToArista(Arista* a, Arista* b) { return (*a < *b); }

vector<Arista*> aristas;

void init() {
	// completar
    long n = F*C;
    altura = new int[n];
    padre = new int[n];
    costCompLider = new int[n];
    cantAristas = new int[n];
    
	for(int i = 0; i < n; i++){
		padre[i] = i;
		altura[i] = 1;
        costCompLider[i] = 0;
        cantAristas[i] = 0;
	}
}

int find(int x) {
	// completar
	if (padre[x] == x) {
		return x;
	}else{
		int p = find(padre[x]);
		padre[x] = p;
		return p;
	}
}

void uni(int x, int y, int costo) {
	// union es una palabra reservada en C++, por eso usamos "uni"
	// completar
    
    //piso con los referentes
	x = find(x); y = find(y);
    
    //checkear vecinos
    
	if(altura[x] == altura[y]) {
		altura[x]++;
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        costCompLider[y] += costCompLider[x]+costo;
	}else if(altura[x] < altura[y]) {
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        costCompLider[y] += costCompLider[x]+costo;
	}else{
		padre[y] = x;
        cantAristas[x] = cantAristas[x]+cantAristas[y]+1;
        costCompLider[x] += costCompLider[y]+costo;
	}
}

void real_pop () {
    //popeo monticulo
    pop_heap(aristas.begin(), aristas.end(), comparePtrToArista);
    //quita el popeado
    aristas.pop_back();
}

int main() {
	
    F = 5;
    C = 9;
    
    //Sirven para saber del grafo cuantos nodos y aristas tengo
    V = 0;
    E = 0;
    
    char map[] = {'#','#','#','#','#','#','#','#','#',
                  '#','0','1','0','#','0','#','0','#',
                  '#','0','#','0','3','0','5','0','#',
                  '#','0','2','0','#','0','#','0','#',
                  '#','#','#','#','#','#','#','#','#'};
    
    init ();
    
    Map = new Node**[F];
    
    //armo la matriz de nodos
    for(int i = 0; i < F; i++){
        Map[i] = new Node*[C];
        for(int j = 0; j < C; j++){
            
            Node *n = new Node();
            n->i = i;
            n->j = j;
            Map[i][j] = n;
            
            char value = map[(i*C)+j];
            if (value == '#') {
                n->value = 10; // los valores van de 0..9 por lo tanto 10 seria inf.
            }else {
                n->value = value - '0';
            }
        }
    }

    //la recorro para armar las aristas
    for(int i = 1; i < F-1; i++){
        for(int j = 1; j < C-1; j++){
            
            Node *actual = Map[i][j];
            actual->visited = true;
            
            if (actual->value != 0) {
                continue;
            }
            
            // Es nodo si es igual a cero!
            V++;
            
            Node *abajo = Map[i+1][j];
 
            if (!(abajo->value == 10)) {
                Arista *a = new Arista();
                a->inicio = (i*C)+j;
                
                if (abajo->value == 0) {
                    a->fin = ((i+1)*C)+j;
                }else {
                    a->fin = ((i+2)*C)+j;
                }
                
                a->costo = abajo->value;
                
                //pusheo monticulo
                aristas.push_back(a);
                //ordeno monticulo
                //push_heap(aristas.begin(), aristas.end(), comparePtrToArista);
                
                E++;
            }
            
            
            Node *derecha = Map[i][j+1];
            
            if (!(derecha->value == 10)) {
                Arista *a = new Arista();
                a->inicio = (i*C)+j;
                
                if (derecha->value == 0) {
                    a->fin = (i*C)+(j+1);
                }else {
                    a->fin = (i*C)+(j+2);
                }
                
                a->costo = derecha->value;
                
                //pusheo monticulo
                aristas.push_back(a);
                //ordeno monticulo
                //push_heap(aristas.begin(), aristas.end(), comparePtrToArista);
                
                E++;
            }
        }
    }
    
	sort(aristas.begin(), aristas.end(), comparePtrToArista); // ordeno las aristas por peso de menor a mayor
    
    //ciclo con monticulo
	//while (aristas.size()) {
    for (int i = 0; i < E; i++) {
        Arista *a = aristas[i];
        
        //pila monticulo
		//Arista *a = aristas.front();
        //popeo la pila
        //real_pop();
        
		if (find(a->inicio) != find(a->fin)) {
			uni(a->inicio, a->fin, a->costo);
        }
	}

    bool resuelto = false;
    for (int i = 0; i < F*C; i++) {
        if (cantAristas[i] == V-1) {
            printf("%d \n", costCompLider[i]);
            resuelto = true;
            break;
        }
    }
    
    if (!resuelto) {
        printf("-1 \n");
    }
    
    return 0;
}

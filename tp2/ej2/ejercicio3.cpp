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
    
    bool operator<(const Arista &a) const
    {
        if (costo != a.costo)
            return costo > a.costo;
        if (inicio != a.inicio)
            return inicio > a.inicio;
        return fin > a.fin;
    }
};

struct Node {
    int i;
    int j;
    int value;
    bool visited; // indica si el nivel fue recorrido
    
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
	//printf("une %d con %d \n", x, y);
	x = find(x); y = find(y);
	if(altura[x] == altura[y]) {
		altura[x]++;
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        //printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[x], costCompLider[y], costo);
        costCompLider[y] += costCompLider[x]+costo;
	}else if(altura[x] < altura[y]) {
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        //printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[x], costCompLider[y], costo);
        costCompLider[y] += costCompLider[x]+costo;
	}else{
		padre[y] = x;
        cantAristas[x] = cantAristas[x]+cantAristas[y]+1;
        //printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[y], costCompLider[x], costo);
        costCompLider[x] += costCompLider[y]+costo;
	}
}

void proccessNode(int i, int j, Node *actual) {
    if (i >= 0 && i < F && j >= 0 && j < C) {
        Node *node = Map[i][j];
        if(!node->visited) { // no comparo contra un nivel anterior
            Arista *a = new Arista();
            a->inicio = (actual->i*C)+actual->j;
            a->fin = (i*C)+j;
            
            if (node->value == 10 || actual->value == 10) {
                a->costo = 20; // Arista no cruzable
            }else {
                a->costo = actual->value+node->value;
            }
            
            //printf("pushea arista (%d, %d) con costo %d \n", a->inicio, a->fin, a->costo);
        
            //pusheo monticulo
            aristas.push_back(a);
            //ordeno monticulo
            push_heap(aristas.begin(), aristas.end(), comparePtrToArista);
        }
    }
}

void real_pop () {
    //popeo monticulo
    pop_heap(aristas.begin(), aristas.end(), comparePtrToArista);
    //quita el popeado
    aristas.pop_back();
}

int main() {
	//cin >> V >> E;
	
    F = 5;
    C = 9;
    
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
    for(int i = 0; i < F; i++){
        for(int j = 0; j < C; j++){
            
            Node *actual = Map[i][j];
            actual->visited = true;
 
            //crea aristas si no existen
            proccessNode(i-1, j, actual);
            proccessNode(i+1, j, actual);
            proccessNode(i, j-1, actual);
            proccessNode(i, j+1, actual);
        }
    }
    
	/*for (int i = 0; i < E; i++) {
		Arista a;
		cin >> a.inicio >> a.fin >> a.costo;
		aristas.push_back(a);
	}*/
	
	//sort(aristas.begin(), aristas.end(), comparePtrToArista); // ordeno las aristas por peso de menor a mayor
	
    //printf("aristas size %lu \n", aristas.size());
    
    int totalDescartable = 0;
    
	while (aristas.size()) {
        //pila monticulo
		Arista *a = aristas.front();
        //popeo la pila
        real_pop();
        
        //printf("popeo arista (%d, %d) con costo %d \n", a->inicio, a->fin, a->costo);
        Node *nodoInicio = Map[a->inicio/C][a->inicio%C];
        Node *nodoFin = Map[a->fin/C][a->fin%C];
        int valorNodoInicio = nodoInicio->value;
        int valorNodoFin = nodoFin->value;
        
		if (find(a->inicio) != find(a->fin) && a->costo < 20 && (valorNodoInicio == 0 || valorNodoFin == 0)) {
			//printf("proceso arista (%d, %d) con costo %d \n", a->inicio, a->fin, a->costo);
			uni(a->inicio, a->fin, a->costo);
        }else {
            //Es una arista que tiene costo igual a otra unida a uno de los extremos de la misma
            //Como forma un ciclo
            if (a->costo < 20) {
                if (valorNodoInicio > 0) {
                    totalDescartable += a->costo;
                }else {
                    totalDescartable += a->costo;
                }
            }
		}
	}

    printf("total descartable %d \n", totalDescartable);
    for (int i = 0; i < F*C; i++) {
        printf("cost comp %d is %d cant aristas %d altura %d \n", i, (costCompLider[i]-totalDescartable)/2, cantAristas[i], altura[i]);
    }
    
    return 0;
}

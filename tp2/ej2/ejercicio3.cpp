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

// el nodo es valido si tiene valor no infinito y esta en una componente que no sea la componente por la cual estoy checkeando.
bool checkNode(int i, int j, int representante) {
    if (i >= 0 && i < F && j >= 0 && j < C) {
        Node *node = Map[i][j];
        //Uso find en lugar de padre[] por si no esta actualizado
        
        if (node->value == 20 || find((i*C)+j) == representante) {
            return false;
        }
        
        printf("valida nodo valor %d indices (%d, %d) \n", node->value, i, j);
        
        return true;
    }
    
    return false;
}

void uni(int x, int y, int costo) {
	// union es una palabra reservada en C++, por eso usamos "uni"
	// completar
    
    Node *nodoInicio = Map[x/C][x%C];
    Node *nodoFin = Map[y/C][y%C];
    int valorNodoInicio = nodoInicio->value;
    int valorNodoFin = nodoFin->value;
    
    //piso con los referentes
	x = find(x); y = find(y);
    
    if (!cantAristas[x] && !cantAristas[y] && valorNodoInicio > 0 && valorNodoFin > 0) {
        //son dos nodos con valor > 0. Esto indica que no hay caminos
        return;
    }else if(!cantAristas[x] && valorNodoInicio > 0) {
        //Estoy uniendo una componente a un nodo con valor mayor que 0.
        //Solo si este nodo es viable puedo continuar.
        
        int ix = x/C;
        int jx = x%C;
        
        //alguno de los vecinos de "x" sera "y", esa dara false por ser su mismo representante
        
        if (!(checkNode(ix-1, jx, y) || checkNode(ix+1, jx, y) || checkNode(ix, jx-1, y) || checkNode(ix, jx+1, y))) {
            return;
        }
        
    }else if(!cantAristas[y] && valorNodoFin > 0) {
        //Estoy uniendo una componente a un nodo con valor mayor que 0.
        //Solo si este nodo es viable puedo continuar.
        
        int iy = y/C;
        int jy = y%C;
        
        //alguno de los vecinos de "y" sera "x", esa dara false por ser su mismo representante
        
        if (!(checkNode(iy-1, jy, x) || checkNode(iy+1, jy, x) || checkNode(iy, jy-1, x) || checkNode(iy, jy+1, x))) {
            return;
        }
    }

    //checkear vecinos
    printf("une %d con %d \n", (nodoInicio->i*C)+nodoInicio->j, (nodoFin->i*C)+nodoFin->j);
    
	if(altura[x] == altura[y]) {
		altura[x]++;
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[x], costCompLider[y], costo);
        costCompLider[y] += costCompLider[x]+costo;
	}else if(altura[x] < altura[y]) {
		padre[x] = y;
        cantAristas[y] = cantAristas[y]+cantAristas[x]+1;
        printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[x], costCompLider[y], costo);
        costCompLider[y] += costCompLider[x]+costo;
	}else{
		padre[y] = x;
        cantAristas[x] = cantAristas[x]+cantAristas[y]+1;
        printf("comp cost %d con comp cost %d y costo %d \n", costCompLider[y], costCompLider[x], costo);
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
	while (aristas.size()) {
        //pila monticulo
		Arista *a = aristas.front();
        //popeo la pila
        real_pop();
        
        //printf("popeo arista (%d, %d) con costo %d \n", a->inicio, a->fin, a->costo);
		if (find(a->inicio) != find(a->fin) && a->costo < 20) {
			//printf("proceso arista (%d, %d) con costo %d \n", a->inicio, a->fin, a->costo);
			uni(a->inicio, a->fin, a->costo);
        }
	}
    
    for (int i = 0; i < F*C; i++) {
        printf("cost comp %d is %d cant aristas %d altura %d \n", i, (costCompLider[i])/2, cantAristas[i], altura[i]);
    }
    
    return 0;
}

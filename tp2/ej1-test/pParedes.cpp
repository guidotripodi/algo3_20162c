#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

using std::queue;

int PMax;
int F;
int C;
bool finalizar;

struct Node {
	int i;
	int j;
	bool visited; // indica si el nivel fue recorrido
	bool marked; // marca para no encolar solo una vez
	bool iAmWall;
	int wallsBroken;
	int distMinToNode;
	Node():      i(0),
				 j(0),
       visited(false),
        marked(false),
       iAmWall(false),
       wallsBroken(-1),
       distMinToNode(-1) {}
};

Node*** Map; // Matriz mapa con Nodos
Node *nodeStart; // marcado por defecto
Node *nodeEnd;

queue<Node*> cola;

int max(int a, int b){
    return (a > b) ? a : b;
}

void proccessNode(int i, int j, Node *actual) {
    if (i > 0 && i < F-1 && j > 0 && j < C-1) {
        Node *node = Map[i][j];
        //printf("actual + si es pared %d actual %d,%d hijo %d,%d \n", actual->wallsBroken+(int)node->iAmWall, actual->i, actual->j, node->i, node->j);
        if (node->wallsBroken == -1 || actual->wallsBroken+(int)node->iAmWall < node->wallsBroken) { // realmente vale? consultar
            if (actual->distMinToNode == -1) {
                //inicializo porque lo voy a usar
                actual->distMinToNode = 0;
            }
            node->distMinToNode = actual->distMinToNode+1;
            node->wallsBroken = actual->wallsBroken+(int)node->iAmWall;
            
            if (node->i == nodeEnd->i && node->j == nodeEnd->j) {
                finalizar = true;
                return;
            }
            
            if(node->wallsBroken <= PMax) {
                cola.push(node);
            }
        }
    }
}

void mazeBfs () {
	cola.push(nodeStart);
	
	while(cola.size()){
		Node *actual = cola.front();
		cola.pop();
		
		int i = actual->i;
		int j = actual->j;

		proccessNode(i-1, j, actual);
		proccessNode(i+1, j, actual);
		proccessNode(i, j-1, actual);
		proccessNode(i, j+1, actual);
        
        if (finalizar) {
            break;
        }
	}
}

int main(){
    
	F = 5;
	C = 9;
	//PMax = 3;
	
    /*
    char map[] = {'#','#','#','#','#','#','#','#','#',
                  '#','o','.','#','#','#','#','x','#',
                  '#','.','.','#','.','#','#','#','#',
                  '#','.','.','.','.','#','#','#','#',
                  '#','#','#','#','#','#','#','#','#'};
*/


for (int l = 1; l < 50; ++l){
    finalizar = false;
        PMax = l;
        F = 50;
        C = 50;

                  char map[F*C];

                 int h = F;
                 int x = C;
                 int cont = 0;
            //armando matriz            
           for (int i = 0; i < h; ++i) {
                for (int j = 0; j < x; ++j) {
                    if (i == 0 || j == 0 || j == x-1 || i == h-1)   {
                        map[(i*x)+j] = '#';
                    }else{ if (i == 1 && j == x-2){
                            map[(i*x)+j] = 'x';
                         }else{ if (i == 1 && j == 1) {
                                    map[(i*x)+j] = 'o';
                                }else{
                                    if ((i == 1 && j != 1 && j != x-2 && cont < l)){
                                        map[(i*x)+j] = '#';
                                        cont++;
                                    }
                                    if ((i == 1 && j % 2 == 1)){
                                        map[(i*x)+j] = '.';
                                    }
                                    if (i > 1 && i < h-1){
                                        map[(i*x)+j] = '#';
                                    }


                                }
                            }
                        }
                    
                }
                cont = 0;
                
        }
                
        
        

/*
                  printf("FILAS: %d\n", F);
   printf("COLUMNAS: %d\n", C);
   printf("PMAX: %d\n", PMax);

    for (int i = 0; i < F; ++i){
            printf("\n");
        for (int j = 0; j < C; ++j) {
            printf("%c",map[(i*C)+j] );
        }
       
    }*/
	auto start = ya();
	Map = new Node**[F];
	
	for(int i = 0; i < F; i++){
		Map[i] = new Node*[C];
		for(int j = 0; j < C; j++){
            
            Node *n = new Node();
            n->i = i;
            n->j = j;
            Map[i][j] = n;
            
            char value = map[(i*C)+j];
            
            if(value == '#'){
                n->iAmWall = true;
            }else if(value == 'o'){
                nodeStart = n;
                n->iAmWall = false;
                n->wallsBroken = 0;
            }else if(value == 'x'){
                nodeEnd = n;
                n->iAmWall = false;
            }else {
                n->iAmWall = false;
            }
		}
	}
	
	mazeBfs();
	//printf("\n");
	//printf("Distancia minima obtenida: %d \n", nodeEnd->distMinToNode);
    /*Descomentar esto para correr la medicion correspondiente*/
  auto end = ya();
            cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
            printf("\n");
            
            for(int i = 0; i < F; i++){
        for(int j = 0; j < C; j++){    
            Node *n = Map[i][j];
            delete n;
        }
        delete[] Map[i];
    }
  
}
	return 0;
}

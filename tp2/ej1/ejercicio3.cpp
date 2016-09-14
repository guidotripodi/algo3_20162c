#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>

using std::queue;

int PMax;
int distMin;
int F;
int C;

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
       wallsBroken(0),
       distMinToNode(0) {}
};

Node*** Map; // Matriz mapa con Nodos
Node *nodeStart; // marcado por defecto
Node *nodeEnd;

queue<Node*> cola;

int max(int a, int b){
    return (a > b) ? a : b;
}

void proccessNode(Node *node, Node *actual) {
	if(!node->visited) { // no comparo contra un nivel anterior
		if (!(actual->iAmWall && node->iAmWall)){
			if (actual->wallsBroken+(int)node->iAmWall < node->wallsBroken) { // realmente vale? consultar
				node->distMinToNode = actual->distMinToNode+1;
				actual->wallsBroken = actual->wallsBroken+(int)node->iAmWall;
				if(!node->marked) { // quiero encolar solo una vez
					node->marked = true;
					cola.push(node);
				}
			}	
		}
	}
}

void mazeBfs () {
	cola.push(nodeStart);
	
	while(cola.size()){
		Node *actual = cola.front();
		cola.pop();
		actual->visited = true;
		int i = actual->i;
		int j = actual->j;
		
		Node *up;
		Node *down;
		Node *left;
		Node *right;
		
		up = Map[i-1][j];
		down = Map[i+1][j];
	 	left = Map[i][j+1];
		right = Map[i][j-1];
		
		proccessNode(up, actual);
		proccessNode(down, actual);
		proccessNode(left, actual);
		proccessNode(right, actual);
	}
}

int main(){
  
	return 0;
}

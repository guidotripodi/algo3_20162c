
struct Node {
	int id;
	bool visited; // indica si el nivel fue recorrido
	int distance;
	Node():      id(0),
		visited(false),
		distance(0) {}
};


int masCercano(int* noVisitados, int* distancia, int cantNodos){
	int minimo;
	int i = 0;
//inicializo el minimo con el primer elemento que exista
//devuelvo -1 si no hay

	while( i < cantNodos ){
		if( noVisitados[i] && distancia[i] != -1){ // no distancia invalida
			minimo = distancia[i];
			break;
		}
		i++;
	}

	if(i == cantNodos) return -1; //visite todos y no encontre un minimo
	
	for(; i < cantNodos; i++){
		if( distancia[i] < minimo && 
				noVisitados[i] &&
				distancia[i] != -1){ // no distancia invalida
			minimo = distancia[i];
		}
	}
	return minimo;
}

int main(){
/*
	function Dijkstra(Graph, source):

	create vertex set Q

	for each vertex v in Graph:             // Initialization
		dist[v] ← INFINITY                  // Unknown distance from source to v
		prev[v] ← UNDEFINED                 // Previous node in optimal path from source
		add v to Q                          // All nodes initially in Q (unvisited nodes)

	dist[source] ← 0                        // Distance from source to source

	while Q is not empty:
		u ← vertex in Q with min dist[u]    // Source node will be selected first
		remove u from Q 

		for each neighbor v of u:           // where v is still in Q.
			alt ← dist[u] + length(u, v)
			if alt < dist[v]:               // A shorter path to v has been found
			dist[v] ← alt 
			prev[v] ← u 

	return dist[], prev[]

If we are only interested in a shortest path between vertices source and target, we can terminate the search after line 13 if u = target. Now we can read the shortest path from source to target by reverse iteration:

	S ← empty sequence
	u ← target
	while prev[u] is defined:                  // Construct the shortest path with a stack S
		insert u at the beginning of S         // Push the vertex onto the stack
		u ← prev[u]                            // Traverse from target to source
	insert u at the beginning of S             // Push the source onto the stack
*/



	//parsear stdin
	
	//crear objeto grafo?
	//el grafo seria una forma facil de averiguar los vecinos y sacar datos de los nodos
	//lista de vecinos (enteros) y un arreglo que contenga los nodos


	int cantidad;
	int distance[cantidad];
	int prev[cantidad];
	
	//la cola de prioridad, true si ya lo visitamos
	bool noVisitados[cantidad];
	
	for(int i = 0; i < cantidad; i++){
		distance[i] = -1;
		prev[i] = -1;
		noVisitados[i] = false;
	}

	distance[0] = 0;
//Si hago un objeto grafo todo lo de arriba va en el constructor

//no sabemos si el grafo es lo suficientemente esparso para
//usar el min heap y no pasarnos en complejidad de O(n cuadrado)
//asi que la cola se hace con arreglo


	int contador = 0; // cuenta estaciones recorridas


	while(!noVisitados.vacio()){//no visitados
		int actual = masCercano(noVisitados, distance);//de los no visitados y ademas lo saca
	
		if(actual == NULL) break; //visite todo
		if(actual == SALIDA) break; //ya tiene una distancia y prev asignados
		
		Cola vecinos = actual.vecinos();// o grafo.vecinos(actual)
		//for(int j = 0; j < vecinos.size(); j++){ //vector, lista enlazada o cola para los vecinos?
		while(!vecinos.vacia()){
			Node v = vecinos.pop();
			int alt = distance[v.id] + grafo.peso(actual, v); //si la distancia la guarda el nodo: v.distance;
			if( alt < distance[v.id] || distance[v.id] == -1){
				distance[v] = alt;
				prev[v] = actual;
			}

		}
		contador++;
	}

	//recorrer el arreglo prev y ahi tengo los vertices necesarios.
	int j = SALIDA;
	printf("%d\n", distance[j]);
	if(distance[j] != -1){
		printf("%d\n", contador); // tengo que llevar cuenta de los niveles recorridos
		while( j >= 0 ){
			printf("%d", j); //imprimo estaciones
			j = prev[j]; //prev[0] esta en -1
		}
	return 0;
}


struct Node {
	int id;
	bool visited; // indica si el nivel fue recorrido
	int distance;
	Node():      id(0),
		visited(false),
		distance(0) {}
};

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



	return 0;
}

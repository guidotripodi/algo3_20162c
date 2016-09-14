package algo3.tp3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class TwoSat {

	private final List<Integer>[] graph;

	/*
	 * Se representa a cada proposicion con dos nodos en el grafo: uno representando
	 * su valor True y otro su valor False (i.e., para cada proposición p hay un nodo
	 * que representa a p y otro que representa a ¬p).
	 * Si tenemos p_0, p_1, ..., p_k proposiciones, tendremos 2*k nodos.
	 * Para cad 0 <= i <= k, el nodo 2*i representa a la proposición p_i,
	 * y el nodo 2 * i + 1 representa a la proposición ¬p_i.
	 */
	public TwoSat(List<Integer>[] graph) {
		this.graph = graph;
	}

	/**
	 * 
	 * @return un array con la asignación de valores true/false para cada proposición,
	 *         o null si la fórmula booleana es insatisfacible
	 */
	public boolean[] solve() {
		int nodesCount = graph.length;
		boolean[] used = new boolean[nodesCount];

		// Topological sort
		List<Integer> dfsOrder = new ArrayList<>();
		for (int node = 0; node < nodesCount; node++) {
			if (!used[node]) {
				buildOrder(node, used, dfsOrder);
			}
		}
		Collections.reverse(dfsOrder);

		// Calculamos componentes fuertemente conexas utilizando el algoritmo
		// de Kosaraju
		@SuppressWarnings("unchecked") List<Integer>[] reversedGraph = new List[nodesCount];
		for (int node = 0; node < nodesCount; node++) {
			reversedGraph[node] = new ArrayList<>();
		}
		for (int node = 0; node < nodesCount; node++) {
			for (int neighbor : graph[node]) {
				reversedGraph[neighbor].add(node);
			}
		}

		int[] stronglyConnComp = new int[nodesCount];
		Arrays.fill(stronglyConnComp, -1);
		int color = 0;
		for (int node = 0; node < nodesCount; node++) {
			if (stronglyConnComp[node] == -1) {
				buildComponents(node, reversedGraph, stronglyConnComp, color++);
			}
		}

		// la fórmula booleana es insatisfacible sii existe una proposición
		// tal que ella y su negación pertenecen a la misma componente
		// fuertemente conexa
		System.out.println("--- " + Arrays.toString(stronglyConnComp));
		for (int i = 0; i < nodesCount; ++i) {
			if (stronglyConnComp[i] == stronglyConnComp[i ^ 1]) {
				System.out.println("Me rompi con el " + i);
				return null;
			}
		}

		boolean[] res = new boolean[nodesCount / 2];
		for (int node = 0; node < nodesCount; node += 2) {
			res[node / 2] = stronglyConnComp[node] > stronglyConnComp[node + 1];
		}

		return res;
	}

	private void buildOrder(int currentNode, boolean[] used, List<Integer> order) {
		used[currentNode] = true;
		for (int neighbor : graph[currentNode]) {
			if (!used[neighbor]) {
				buildOrder(neighbor, used, order);
			}
		}
		order.add(currentNode);
	}

	private void buildComponents(int currentNode, List<Integer>[] reverseGraph, int[] component, int color) {
		component[currentNode] = color;
		for (int neighbor : reverseGraph[currentNode]) {
			if (component[neighbor] == -1) {
				buildComponents(neighbor, reverseGraph, component, color);
			}
		}
	}
}

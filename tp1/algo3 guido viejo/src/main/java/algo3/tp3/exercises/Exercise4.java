package algo3.tp3.exercises;

import algo3.tp3.graph.GraphBuilder;
import algo3.tp3.graph.Graph;

public class Exercise4 implements ListColoringAlgorithm {

	/*
	 * Esta heuristica busca mejorar en cada paso una solucion obtenida previamente.
	 * Para eso, se utiliza la idea explicada anteriormente de "mejor color" de nodo. Es decir, se pinta a
	 * cada nodo del mejor color posible. Cuando no se puede mejorar ningun nodo, se termina el algoritmo.
	 * 
	 * Mas detalladamente, se realizan pasadas. Para cada pasada, por cada nodo, se pinta del "localmente"
	 * mejor color. Registrandose si en algun momento de la pasada se produjo una mejora en la cantidad
	 * de aristas "buenas". Si luego de la pasada se registra alguna mejora, se realiza otra pasada, de lo
	 * contrario, el algoritmo termina.
	 * 
	 * Se puede demostrar facilmente que el algoritmo termina. Supongamos que el algoritmo no termina,
	 * luego, en cada iteracion aumenta la cantidad de "aristas buenas", lo que implica que la cantidad
	 * posible de aristas buenas no esta acotada. Luego, como la cantidad de aristas buenas es menor a la
	 * cantidad total de aristas, que esta acotada, llegamos a un absurdo, que vino de suponer que el algoritmo
	 * no termina.
	 * 
	 * Con esta idea, podemos generar una cota superior para la cantidad de iteraciones del algoritmo. Esta se da
	 * si en cada pasada aumentamos en 1 la cantidad de aristas buenas. Por lo tanto, como mucho se realizan E pasdas.
	 * Y un vez acotada la cantidad de pasadas del algoritmo podemos calcular su complejidad en el peor caso.
	 * Como en cada pasada se itera por todos los nodos y se pinta del "mejor color", y ademas sabiendo que pintar del
	 * mejor color tiene costo O(E), podemos afirmar que la complejidad de cada pasada es O(V * E).
	 * Ahora bien, como realizamos como mucho E pasdas, el algoritmo tiene complejidad O(V * E^2) en el peor caso.
	 * 
	 * 
	 * 
	 */

	public Graph solve(Graph graphStatus) {
		boolean improved = true;
		while (improved) {
			improved = false;
			for (int node = 0; node < graphStatus.size(); node++) {
				improved = graphStatus.setLocallyBestColor(node) || improved;
			}
		}
		return graphStatus;
	}

	public static void main(String[] args) {
		int i = 10;
		double sum1 = 0, sum2 = 0;
		while (i > 0) {
			Graph g = GraphBuilder.buildRandomGraph(250, 0.7, 50);
			sum1 += new Exercise4().solve(g).getEdgeColoringRatio();
			sum2 += new Exercise4B().solve(g).getEdgeColoringRatio();
			i--;
		}
		System.out.println(sum1 / 1000);
		System.out.println(sum2 / 1000);
	}

}

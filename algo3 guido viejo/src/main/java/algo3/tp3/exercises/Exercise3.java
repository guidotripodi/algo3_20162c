package algo3.tp3.exercises;

import java.util.Arrays;

import algo3.tp3.ValueSortedMap;
import algo3.tp3.graph.GraphBuilder;
import algo3.tp3.graph.Graph;

public class Exercise3 implements ListColoringAlgorithm {

	/*
	 * Este algoritmo representa a una heuristica golosa constructiva.
	 * El algoritmo se basa en la idea intuitiva de que es conveniente empezar a pintar primedo los nodos
	 * con mas restricciones, dejando los nodos con menos restricciones para el final.
	 * Esto se debe a que cuando fijamos un color en un nodo, aumentamos las restricciones de sus vecinos,
	 * ya que estos ahora no tienen este color como opcion. Por lo tanto, si hacemos lo contrario y empezamos
	 * por los nodos con menos restricciones, en cada paso tendremos nodos con "pocas" opciones, lo que hara
	 * mas probable que se nos agoten las opciones mas rapidamente.
	 * 
	 * Mas detalladamente, lo que hace nuestra heuristica es, ordenar a los nodos por su
	 * cantidad de opciones dentro de una estructura que permite tomar el elemento de menor
	 * clave y actualizar el valor de la clave de cualquier elemento.
	 * Luego, mientras haya nodos sin pintar, toma el de menor cantidad de opciones y lo pinta del color
	 * "mas conveniente". Luego de esto, como pintar un nodo reduce la cantidad de opciones de sus vecinos,
	 * actualiza esto, se actualiza en la estructura antes mencionada la cantidad de opciones de los vecinos.
	 * 
	 * Cuando hablamos de pintar del "color mas conveniente" nos referimos al color que genera menos conflictos
	 * con sus vecinos ya pintados. Esto se puede calcular mirando los colores de los vecinos ya pintados
	 * y tomar el que esta dentro de los colores posibles del nodo que aparece menos veces.
	 * 
	 * Para nuestra facilidad, implementamos una estructura que habla del estado del grafo
	 * que esta siendo coloreado. Esta estructura brinda la siguiente informacion cada una
	 * en complejidad O(1):
	 * -Para un nodo indica las opciones de coloreo que no generan conflictos
	 * -Devuelve la cantidad de aristas con sus dos extremos pintados y de distinto color
	 * -Indica el color actual para cada nodo
	 * -Indica si un nodo esta coloreado
	 * 
	 * Y admite las siguientes operaciones:
	 * -Pintar un nodo del "mejor color". Esto, ademas de modificar el color actual del nodo dado, tambien modifica
	 * las restricciones de sus vecinos. Se realiza en complejidad O(#vecinos del nodo) asumiendo
	 * que el agregar/eliminar/modificar es O(1) en tablas de hash.
	 * 
	 * El algoritmo recorre todos los vertices, tomando siempre el menor de la estructura de datos antes mencionada
	 * y a cada uno lo pinta del "mejor color". Luego, actualiza a los vecinos en la estructura de datos.
	 * 
	 * Por lo tanto, la complejidad del algoritmo esta atada a la complejidad de la estructura de datos utilizada.
	 * Nuestra implementacion realiza tanto la operacion de eliminacion del minimo como la operacion de modificacion
	 * de clave en O(log(tamaño)).
	 * 
	 * Ahora bien, en cada iteracion realizamos los siguientes pasos:
	 * + Se remueve el minimo de la estructura. Costo O(log(V))
	 * + Se lo pinta del "mejor color posible". Costo O(#vecinos), como en el peor caso podria estar conectado
	 * con todos sus vecinos, equivale a O(E).
	 * + Para cada vecino se actualiza su nueva cantidad de colores posibles o "grado de libertad". Esto tiene
	 * costo logaritmico para cada vecino, lo que equivale a O(E * log(V)).
	 * 
	 * Si sumamos, da un total de O(E * log(V)) por iteracion, como realizamos V iteraciones, el algoritmo resulta
	 * O(E * V * log(V)) en el peor caso.
	 * 
	 * 
	 *
	 * 
	 * 
	 * 
	 * 
	 */

	public Graph solve(Graph graphStatus) {
		ValueSortedMap<Integer, Integer> nodeColorOpts = new ValueSortedMap<>();
		for (int node = 0; node < graphStatus.size(); node++)
			nodeColorOpts.put(node, graphStatus.getColorOptions(node).size());

		while (!nodeColorOpts.isEmpty()) {
			int node = nodeColorOpts.popMinValueKey();
			graphStatus.setLocallyBestColor(node);

			for (int neighbour : graphStatus.getNeighbours(node)) {
				if (!graphStatus.isColored(neighbour)) {
					nodeColorOpts.put(neighbour, graphStatus.getColorOptions(neighbour).size());
				}
			}

		}

		return graphStatus;

	}

	public static void main(String[] args) {

		Graph g = GraphBuilder.findCounterExample(new Exercise3(), 6, 0.7, 4);

		GraphBuilder builder = new GraphBuilder(6);
		builder.setNeighbours(0, 2);
		builder.setNeighbours(0, 3);
		builder.setNeighbours(0, 4);
		builder.setNeighbours(0, 5);

		builder.setNeighbours(1, 3);
		builder.setNeighbours(1, 4);
		builder.setNeighbours(1, 5);

		builder.setNeighbours(2, 3);
		builder.setNeighbours(2, 5);

		builder.setNeighbours(3, 4);
		builder.setNeighbours(3, 5);

		builder.setNeighbours(4, 5);

		builder.addPossibleColors(0, Arrays.asList(0, 1));
		builder.addPossibleColors(1, Arrays.asList(0, 1, 3));
		builder.addPossibleColors(2, Arrays.asList(2, 3));
		builder.addPossibleColors(3, Arrays.asList(0, 2, 3));
		builder.addPossibleColors(4, Arrays.asList(0, 1, 3));
		builder.addPossibleColors(5, Arrays.asList(0, 2, 3));

		g = builder.build();

		// g = GraphBuilder.buildRandomGraph(2, 1, 2);
		System.out.println(g);
		System.out.println(new Exercise4().solve(g).getNodeColoring());
		System.out.println(new Exercise3().solve(g).getEdgeColoringRatio());
		System.out.println(new Exercise2().solve(g).getNodeColoring());
		System.out.println(new Exercise2().solve(g).getEdgeColoringRatio());
	}

}

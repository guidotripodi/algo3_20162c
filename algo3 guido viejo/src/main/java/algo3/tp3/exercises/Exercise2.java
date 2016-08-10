package algo3.tp3.exercises;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import algo3.tp3.ValueSortedMap;
import algo3.tp3.graph.GraphBuilder;
import algo3.tp3.graph.Graph;

public class Exercise2 implements ListColoringAlgorithm {

	public Graph solve(Graph graphStatus) {
		ValueSortedMap<Integer, Integer> nodeColorOpts = new ValueSortedMap<>();
		for (int node = 0; node < graphStatus.size(); node++)
			nodeColorOpts.put(node, graphStatus.getColorOptions(node).size());
		backtrack(graphStatus, nodeColorOpts);
		return graphStatus;
	}

	private boolean backtrack(Graph graphStatus, ValueSortedMap<Integer, Integer> nodeColorOpts) {
		if (nodeColorOpts.isEmpty())
			return true;
		if (nodeColorOpts.getMinValue() == 0) //Si hay un nodo sin opciones, no se puede!
			return false;
		//if (nodeColorOpts.getMaxValue() <= 2)
			//return new Exercise1().solve(graphStatus);
		int nextNode = nodeColorOpts.popMaxValueKey();
		for (int color : getColorOptions(nextNode, graphStatus)) {
			setColorAndUpdateNeighbourColorOptions(nextNode, color, graphStatus, nodeColorOpts);
			if (backtrack(graphStatus, nodeColorOpts))
				return true;
		}
		setColorAndUpdateNeighbourColorOptions(nextNode, Graph.NOT_COLORED_COLOR, graphStatus, nodeColorOpts);
		nodeColorOpts.put(nextNode, graphStatus.getColorOptions(nextNode).size());
		return false;
	}

	void setColorAndUpdateNeighbourColorOptions(int node, int color, Graph graphStatus,
			ValueSortedMap<Integer, Integer> nodeColorOpts) {
		graphStatus.setCurrentColor(node, color);
		for (int neighbour : graphStatus.getNeighbours(node)) {
			if (!graphStatus.isColored(neighbour)) {
				nodeColorOpts.put(neighbour, graphStatus.getColorOptions(neighbour).size());
			}
		}
	}

	/*
	 * Poda de "colores faciles". Si un nodo tiene un color como opcion que ninguno de sus
	 * vecinos pintados tiene, entonces ese color es "facil" para ese nodo. Resulta evidente
	 * que hay que pintar al nodo de ese color, ya que es imposible que genere conflictos con
	 * sus vecinos.
	 */
	private Set<Integer> getColorOptions(int node, Graph graphStatus) {
		int easyColor = graphStatus.getEasyColor(node);
		if (easyColor != Graph.NOT_COLORED_COLOR) {
			return Collections.singleton(easyColor);
		}
		return new HashSet<>(graphStatus.getColorOptions(node));
	}

	public static void main(String[] args) {
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

		Graph g = builder.build();

		// g = GraphBuilder.buildRandomGraph(2, 1, 2);
		System.out.println(g);
		System.out.println(new Exercise2().solve(g).getNodeColoring());
		System.out.println(new Exercise2().solve(g).getEdgeColoringRatio());
	}

}

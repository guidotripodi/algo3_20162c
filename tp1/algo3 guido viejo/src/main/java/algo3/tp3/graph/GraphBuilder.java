package algo3.tp3.graph;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;

import algo3.tp3.exercises.Exercise2;
import algo3.tp3.exercises.ListColoringAlgorithm;

public class GraphBuilder {

	private static final int COUNTER_EXAMPLE_RETRIES = 100000;

	private int size;
	private final List<Set<Integer>> neighboursList;
	private final List<Set<Integer>> possibleColors;

	public GraphBuilder(int size) {
		this.size = size;
		neighboursList = new ArrayList<>(size);
		possibleColors = new ArrayList<>(size);
		for (int i = 0; i < size; i++) {
			neighboursList.add(new HashSet<Integer>());
			possibleColors.add(new HashSet<Integer>());
		}
	}

	public void setNeighbours(int node1, int node2) {
		neighboursList.get(node1).add(node2);
		neighboursList.get(node2).add(node1);
	}

	public void addPossibleColors(int node, List<Integer> colors) {
		possibleColors.get(node).addAll(colors);
	}

	public Graph build() {
		return new Graph(size, neighboursList, possibleColors);
	}

	public static Graph buildColorableGraph(int size, double neighboursProbability,
			int colorCount) {
		Graph ret = null;
		int retries = COUNTER_EXAMPLE_RETRIES;
		Exercise2 backtrackingSolver = new Exercise2();
		while (retries > 0 && ret == null) {
			Graph randomGraph = buildRandomGraph(size, neighboursProbability, colorCount);
			if (backtrackingSolver.solve(randomGraph).completelyColored())
				ret = randomGraph;
			retries--;
		}
		return ret;
	}

	public static Graph findCounterExample(ListColoringAlgorithm algorithm, int size, double neighboursProbability,
			int colorCount) {
		Graph ret = null;
		int retries = COUNTER_EXAMPLE_RETRIES;
		while (retries > 0 && ret == null) {
			Graph colorableGraph = buildColorableGraph(size, neighboursProbability, colorCount);
			if (colorableGraph != null && !algorithm.solve(colorableGraph).completelyColored())
				ret = colorableGraph;
			retries--;
		}
		return ret;
	}

	public static Graph buildRandomGraph(int size, double neighboursProbability, int colorCount) {
		List<Integer> colors = new ArrayList<>();
		for (int i = 0; i < colorCount; i++) {
			colors.add(i);
		}
		Random random = new Random();
		GraphBuilder builder = new GraphBuilder(size);
		for (int node1 = 0; node1 < size; node1++) {
			for (int node2 = node1 + 1; node2 < size; node2++) {
				if (random.nextDouble() <= neighboursProbability) {
					builder.setNeighbours(node1, node2);
				}
			}
			Collections.shuffle(colors, random);
			int nodeColorCount = random.nextInt(colors.size() - 1) + 1;
			builder.addPossibleColors(node1, colors.subList(0, nodeColorCount));
		}
		return builder.build();

	}

}

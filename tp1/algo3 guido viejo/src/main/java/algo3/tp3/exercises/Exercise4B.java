package algo3.tp3.exercises;

import algo3.tp3.graph.Graph;

public class Exercise4B implements ListColoringAlgorithm {

	@Override
	public Graph solve(Graph graphStatus) {
		for (int node = 0; node < graphStatus.size(); node++) {
			int color = graphStatus.getPossibleColors(node).iterator().next();
			graphStatus.setCurrentColor(node, color);
		}
		boolean mayImprove = !graphStatus.completelyColored();
		while (mayImprove) {
			mayImprove = false;
			for (int node = 0; node < graphStatus.size(); node++) {
				int currentColor = graphStatus.getCurrentColor(node);
				for (int color : graphStatus.getPossibleColors(node)) {
					boolean nodeImproved = graphStatus.setCurrentColor(node, color);
					if (nodeImproved) {
						mayImprove = true;
						break;
					} else {
						graphStatus.setCurrentColor(node, currentColor);
					}
				}
			}
		}
		return graphStatus;
	}

	public static void main(String[] args) {
		System.out.println("a\tb");
//		GraphBuilder builder = new GraphBuilder(6);
//		builder.setNeighbours(0, 2);
//		builder.setNeighbours(0, 3);
//		builder.setNeighbours(0, 4);
//		builder.setNeighbours(0, 5);
//
//		builder.setNeighbours(1, 3);
//		builder.setNeighbours(1, 4);
//		builder.setNeighbours(1, 5);
//
//		builder.setNeighbours(2, 3);
//		builder.setNeighbours(2, 5);
//
//		builder.setNeighbours(3, 4);
//		builder.setNeighbours(3, 5);
//
//		builder.setNeighbours(4, 5);
//
//		builder.addPossibleColors(0, Arrays.asList(0, 1));
//		builder.addPossibleColors(1, Arrays.asList(0, 1, 3));
//		builder.addPossibleColors(2, Arrays.asList(2, 3));
//		builder.addPossibleColors(3, Arrays.asList(0, 2, 3));
//		builder.addPossibleColors(4, Arrays.asList(0, 1, 3));
//		builder.addPossibleColors(5, Arrays.asList(0, 2, 3));
//
//		Graph g = builder.build();
//
//		// g = GraphBuilder.buildRandomGraph(2, 1, 2);
//		System.out.println(g);
//		System.out.println(new Exercise4B().solve(g).getNodeColoring());
//		System.out.println(new Exercise4B().solve(g).getEdgeColoringRatio());
//		System.out.println(new Exercise2().solve(g).getNodeColoring());
//		System.out.println(new Exercise2().solve(g).getEdgeColoringRatio());
	}

}

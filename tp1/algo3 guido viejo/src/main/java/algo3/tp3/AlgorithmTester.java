package algo3.tp3;

import algo3.tp3.exercises.Exercise2;
import algo3.tp3.exercises.ListColoringAlgorithm;
import algo3.tp3.graph.GraphBuilder;
import algo3.tp3.graph.Graph;

public class AlgorithmTester {

	private static int EXAMPLES = 100;

	public static void testWithColorable(ListColoringAlgorithm algorithm1, ListColoringAlgorithm algorithm2,
			ListColoringAlgorithm algorithm3, int size,
			double edgeProbability,
			int colorCount) {
		double sum1 = 0, sum2 = 0, sum3 = 0;
		for (int i = 0; i < EXAMPLES; i++) {
			// Graph g = GraphBuilder.buildColorableGraph(size, edgeProbability, colorCount);
			Graph g = GraphBuilder.buildRandomGraph(size, edgeProbability, colorCount);
			
			long t1 = System.currentTimeMillis();
			algorithm1.solve(g);
			sum1 += System.currentTimeMillis() - t1;
			
			t1 = System.currentTimeMillis();
			algorithm2.solve(g);
			sum2 += System.currentTimeMillis() - t1;
			
			t1 = System.currentTimeMillis();
			algorithm3.solve(g);
			sum3 += System.currentTimeMillis() - t1;
		}
		sum1 /= EXAMPLES;
		sum2 /= EXAMPLES;
		sum3 /= EXAMPLES;

		sum1 = ((double) ((int) (sum1 * 1000))) / 1000;
		sum2 = ((double) ((int) (sum2 * 1000))) / 1000;
		sum3 = ((double) ((int) (sum3 * 1000))) / 1000;

		System.out.println(size + "\t" + sum1 + "\t" + sum2 + "\t" + sum3);
	}

	public static void main(String[] args) {
		for (int i = 10; i < 100; i++) {
			//testWithColorable(new Exercise2(), new Exercise2B(), new Exercise2C(), i, 0.9, i/4);
		}
	}

}

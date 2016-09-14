package algo3.tp3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class Exercise1 {

	public static ListColoringResult solve(ListColoringInput input) {
		/*
		 * Para transformar el problema en una instancia del problema de 2-SAT, realizamos la siguiente transformación:
		 * Pensamos a cada nodo como una proposición. Por ejemplo, si al nodo i lo asociamos con la proposición x,
		 * decimos que x := true equivale a que el nodo i-ésimo esté pintado del primer color, y x := false equivale
		 * a que el nodo esté pintado del segundo color.
		 * 
		 * De este modo, supongamos que tenemos dos nodos adyacentes i y j tal que el primer color de i
		 * es igual al segundo color de j. Entonces, como deben tener colores distintos, para satisfacer list-coloring
		 * debe suceder que i esté pintado del segundo color o que j esté pintado del primer color. Si asociamos a los
		 * i y j con las proposiciones p y q respectivamente, la afirmación anterior es equivalente a (¬p v q).
		 * Los demás casos son análogos.
		 */

		List<Edge> edges = input.getEdges();
		List<List<Integer>> posibleColors = input.getPosibleColors();

		@SuppressWarnings("unchecked") List<Integer>[] twoSatGraph =
				(List<Integer>[]) new List[2 * posibleColors.size()];

		for (int i = 0; i < twoSatGraph.length; i++) {
			twoSatGraph[i] = new ArrayList<>();
		}

		for (Edge edge : edges) {
			int firstNode = edge.getFirstNode(), secondNode = edge.getSecondNode();

			int firstTrue = 2 * firstNode, firstFalse = 2 * firstNode + 1;
			int secondTrue = 2 * secondNode, secondFalse = 2 * secondNode + 1;

			int[] firstColors = getColors(posibleColors.get(firstNode));
			int[] secondColors = getColors(posibleColors.get(secondNode));

			if (firstColors[0] == secondColors[0]) {
				// Si representamos a los nodos con las proposiciones x e y, esto es equivalente a
				// (¬x v ¬y), que es equivalente a (x => ¬y) ^ (y => ¬x). Los otros casos son análogos.
				twoSatGraph[firstTrue].add(secondFalse);
				twoSatGraph[secondTrue].add(firstFalse);
			}
			if (firstColors[0] == secondColors[1]) {
				twoSatGraph[firstTrue].add(secondTrue);
				twoSatGraph[secondFalse].add(firstFalse);
			}
			if (firstColors[1] == secondColors[0]) {
				twoSatGraph[firstFalse].add(secondFalse);
				twoSatGraph[secondTrue].add(firstTrue);
			}
			if (firstColors[1] == secondColors[1]) {
				twoSatGraph[firstFalse].add(secondTrue);
				twoSatGraph[secondFalse].add(firstTrue);
			}
		}

		boolean[] twoSatResult = new TwoSat(twoSatGraph).solve();
		System.out.println(Arrays.toString(twoSatGraph));
		System.out.println(Arrays.toString(twoSatResult));
		int[] assignment = null;
		if (twoSatResult != null) {
			assignment = new int[posibleColors.size()];
			for (int i = 0; i < posibleColors.size(); i++) {
				int[] nodeColors = getColors(posibleColors.get(i));
				assignment[i] = twoSatResult[i] ? nodeColors[0] : nodeColors[1];
			}
		}

		return new ListColoringResult(assignment);

	}

	// firstColors[firstPos] == secondColors[secondPoS]
	private static void addEdge(int[] firstColors, int[] secondColors, int firstPos, int secondPos,
			List<Integer>[] graph) {
		
	}
	// 9 14 4
	// 2 1 2
	// 2 0 1
	// 1 1
	// 2 0 3
	// 2 0 2
	// 2 0 1
	// 2 1 2
	// 2 2 3
	// 2 1 2
	// 0 1
	// 0 7
	// 1 7
	// 3 7
	// 1 3
	// 1 2
	// 3 4
	// 2 4
	// 4 5
	// 4 6
	// 2 5
	// 2 8
	// 8 6
	// 5 6

	private static int[] getColors(List<Integer> colors) {
		if (colors.size() == 1) {
			int color = colors.get(0);
			return new int[] {color, color};
		} else { // color.size() == 2
			int first = colors.get(0), second = colors.get(1);
			return new int[] {first, second};
		}
	}

	public static class ListColoringResult {

		private int[] assignment;

		public ListColoringResult(int[] assignment) {
			this.assignment = assignment;
		}

		public boolean isPossible() {
			return assignment != null;
		}

		public int getColor(int node) {
			return assignment[node];
		}

	}

	static class Edge {

		private final int firstNode;
		private final int secondNode;

		public Edge(int firstNode, int secondNode) {
			this.firstNode = firstNode;
			this.secondNode = secondNode;
		}

		public int getFirstNode() {
			return firstNode;
		}

		public int getSecondNode() {
			return secondNode;
		}

	}

	public static class ListColoringInput {

		private final List<List<Integer>> posibleColors;
		private final List<Edge> edges;

		public ListColoringInput(List<List<Integer>> posibleColors, List<Edge> edges) {
			this.posibleColors = posibleColors;
			this.edges = edges;
		}

		public List<Edge> getEdges() {
			return edges;
		}

		public List<List<Integer>> getPosibleColors() {
			return posibleColors;
		}

	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer firstRow = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(firstRow.nextToken());
		int m = Integer.parseInt(firstRow.nextToken());
		int c = Integer.parseInt(firstRow.nextToken());
		List<List<Integer>> possibleColors = new ArrayList<>();
		for (int node = 0; node < n; node++) {
			List<Integer> nodeColoring = new ArrayList<>();
			StringTokenizer line = new StringTokenizer(br.readLine());
			int t = Integer.parseInt(line.nextToken());
			for (int i = 0; i < t; i++) {
				int color = Integer.parseInt(line.nextToken());
				nodeColoring.add(color);
			}
			possibleColors.add(nodeColoring);
		}
		List<Edge> edges = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			StringTokenizer edgeRow = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(edgeRow.nextToken());
			int b = Integer.parseInt(edgeRow.nextToken());
			edges.add(new Edge(a, b));
		}
		ListColoringInput input = new ListColoringInput(possibleColors, edges);
		ListColoringResult solve = solve(input);
		for (int i = 0; i < n; i++) {
			System.out.println(i + " -> " + solve.getColor(i));
		}

	}

}

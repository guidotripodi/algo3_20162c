package algo3.tp2.ej3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Exercise3 {

	public static int solve(Exercise2Input input) {
		UnionFind unionFind = new UnionFind(input.getNodesCount());
		List<Corridor> corridors = input.getCorridors();
		Collections.sort(corridors);
		int result = 0;
		for (Corridor corridor : corridors) {
			if (unionFind.find(corridor.getFirstIntersection()) != unionFind.find(corridor.getSecondIntersection())) {
				unionFind.union(corridor.getFirstIntersection(), corridor.getSecondIntersection());
			} else {
				result += corridor.getLength();
			}
		}
		return -result;
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String corridorsStr = br.readLine();
		Exercise2Input input = parseInput(corridorsStr);
		System.out.println(solve(input));
	}

	public static Exercise2Input parseInput(String corridorsStr) {
		String[] splittedCorridors = corridorsStr.split("; ");
		int lastNode = 0;
		List<Corridor> corridors = new ArrayList<Corridor>();
		for (String corridorStr : splittedCorridors) {
			String[] splitted = corridorStr.split(" ");
			int from = Integer.parseInt(splitted[0]);
			int to = Integer.parseInt(splitted[1]);
			int length = Integer.parseInt(splitted[2]);
			corridors.add(new Corridor(from, to, -length));
			lastNode = Math.max(lastNode, Math.max(from, to));
		}
		return new Exercise2Input(lastNode + 1, corridors);
	}

	private static class Exercise2Input {

		private final int nodesCount;
		private final List<Corridor> corridors;

		public Exercise2Input(int nodesCount, List<Corridor> corridors) {
			this.nodesCount = nodesCount;
			this.corridors = corridors;
		}

		public int getNodesCount() {
			return nodesCount;
		}

		public List<Corridor> getCorridors() {
			return corridors;
		}

	}
}

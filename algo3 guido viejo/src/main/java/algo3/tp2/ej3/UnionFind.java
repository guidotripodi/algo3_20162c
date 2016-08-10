package algo3.tp2.ej3;

import java.util.ArrayList;
import java.util.List;

public class UnionFind {

	private List<Integer> ranks;
	private List<Integer> parent;

	public UnionFind(int nodesCount) {
		this.ranks = new ArrayList<Integer>(nodesCount);
		this.parent = new ArrayList<Integer>(nodesCount);
		for (int i = 0; i < nodesCount; i++) {
			ranks.add(0);
			parent.add(i);
		}
	}

	public int find(int node) {
		if (parent.get(node) != node) {
			parent.set(node, find(parent.get(node)));
		}
		return parent.get(node);
	}

	public void union(int firstNode, int secondNode) {
		int firstRoot = find(firstNode);
		int secondRoot = find(secondNode);
		if (ranks.get(firstRoot) < ranks.get(firstRoot)) {
			parent.set(firstRoot, secondRoot);
		} else {
			parent.set(secondRoot, firstRoot);
		}
		if (ranks.get(firstRoot) == ranks.get(firstRoot)) {
			ranks.set(firstRoot, ranks.get(firstRoot) + 1);
		}
	}

}

package algo3.tp3.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Graph {

	public final static int NOT_COLORED_COLOR = -1;

	private int coloredNodes;
	private int goodEdges;
	private final List<Map<Integer, Integer>> prohibitedColors;
	private final List<Integer> nodeColor;
	private final List<Set<Integer>> colorOptions;

	private final int size;
	private final List<Set<Integer>> neighbours;
	private final List<Set<Integer>> possibleColors;
	private int edgesCount;

	public Graph(int size, List<Set<Integer>> neighbours, List<Set<Integer>> possibleColors) {
		this.size = size;
		this.neighbours = neighbours;
		this.possibleColors = possibleColors;
		this.edgesCount = 0;
		for (Set<Integer> nodeNeighbours : neighbours) {
			this.edgesCount += nodeNeighbours.size();
		}
		this.edgesCount /= 2;

		this.coloredNodes = 0;
		this.goodEdges = 0;
		this.nodeColor = new ArrayList<>();
		this.colorOptions = new ArrayList<>();
		this.prohibitedColors = new ArrayList<>();
		for (int node = 0; node < size; node++) {
			this.prohibitedColors.add(new HashMap<Integer, Integer>());
			this.colorOptions.add(new HashSet<>(getPossibleColors(node)));
			this.nodeColor.add(NOT_COLORED_COLOR);
		}
	}

	public int getEdgesCount() {
		return edgesCount;
	}

	public int size() {
		return size;
	}

	public Set<Integer> getNeighbours(int node) {
		return neighbours.get(node);
	}

	public Set<Integer> getPossibleColors(int node) {
		return possibleColors.get(node);
	}

	public String toString() {
		return "vecinos: " + neighbours.toString() + "\n" + "colores_posibles: " + possibleColors;
	}

	public void reset() {
		for (int node = 0; node < size(); node++) {
			setCurrentColor(node, NOT_COLORED_COLOR);
		}
	}

	public List<Integer> getNodeColoring() {
		return nodeColor;
	}

	public boolean completelyColored() {
		return goodEdges == getEdgesCount();
	}

	public double getEdgeColoringRatio() {
		return (double) goodEdges / getEdgesCount();
	}

	public Set<Integer> getColorOptions(int node) {
		return colorOptions.get(node);
	}

	public int getGoodEdges() {
		return goodEdges;
	}

	public int getColoredNodes() {
		return coloredNodes;
	}

	public int getCurrentColor(int node) {
		return nodeColor.get(node);
	}

	public boolean isColored(int node) {
		return getCurrentColor(node) != NOT_COLORED_COLOR;
	}

	public int getEasyColor(int node) {
		Set<Integer> currentOptions = new HashSet<>(getColorOptions(node));
		for (int neighbour : getNeighbours(node)) {
			if (!isColored(neighbour)) {
				currentOptions.removeAll(getColorOptions(neighbour));
			}
		}
		return currentOptions.isEmpty() ? NOT_COLORED_COLOR : currentOptions.iterator().next();
	}

	public boolean setCurrentColor(int node, int newColor) {
		int oldGoodEdges = goodEdges;
		int oldColor = nodeColor.get(node);
		if (oldColor != NOT_COLORED_COLOR)
			coloredNodes--;
		if (newColor != NOT_COLORED_COLOR)
			coloredNodes++;
		nodeColor.set(node, newColor);
		for (int neighbour : getNeighbours(node)) {
			removeColorProhibition(neighbour, oldColor);
			addColorProhibition(neighbour, newColor);
			int neighbourColor = getCurrentColor(neighbour);
			if (neighbourColor != NOT_COLORED_COLOR) {
				if (oldColor != NOT_COLORED_COLOR && oldColor != neighbourColor)
					goodEdges--;
				if (newColor != NOT_COLORED_COLOR && newColor != neighbourColor)
					goodEdges++;
			}
		}
		return goodEdges > oldGoodEdges;
	}

	public boolean setLocallyBestColor(int node) {
		return setCurrentColor(node, getLocallyBestColor(node));
	}

	private int getLocallyBestColor(int node) {
		Map<Integer, Integer> neighboursColorCount = new HashMap<>();
		for (int neighbour : getNeighbours(node)) {
			int color = nodeColor.get(neighbour);
			if (color != NOT_COLORED_COLOR) {
				Integer count = neighboursColorCount.get(color);
				if (count == null) {
					count = 0;
					neighboursColorCount.put(color, count);
				}
				neighboursColorCount.put(color, count + 1);
			}
		}
		int bestColor = getPossibleColors(node).iterator().next();
		Integer bestColorCount = neighboursColorCount.get(bestColor); // Tiene que existir!
		if (bestColorCount == null) {
			bestColorCount = 0;
		}
		for (int color : getPossibleColors(node)) {
			Integer colorCount = neighboursColorCount.get(color);
			if (colorCount == null)
				colorCount = 0;
			if (colorCount < bestColorCount) {
				bestColorCount = colorCount;
				bestColor = color;
			}
		}
		return bestColor;
	}

	private void addColorProhibition(int node, int color) {
		if (color != NOT_COLORED_COLOR) {
			if (getPossibleColors(node).contains(color)) {
				colorOptions.get(node).remove(color);
			}
			Integer prohibitionCount = prohibitedColors.get(node).get(color);
			if (prohibitionCount == null) {
				prohibitionCount = 0;
			}
			prohibitedColors.get(node).put(color, prohibitionCount + 1);
		}
	}

	private void removeColorProhibition(int node, int color) {
		if (color != NOT_COLORED_COLOR) {
			Integer prohibitionCount = prohibitedColors.get(node).get(color);
			if (prohibitionCount != null) {
				if (prohibitionCount == 1) {
					prohibitedColors.get(node).remove(color);
					if (getPossibleColors(node).contains(color)) {
						colorOptions.get(node).add(color);
					}
				} else {
					prohibitedColors.get(node).put(color, prohibitionCount - 1);
				}
			}
		}
	}

}

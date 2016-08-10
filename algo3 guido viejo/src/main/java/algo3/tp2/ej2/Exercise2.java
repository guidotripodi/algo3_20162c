package algo3.tp2.ej2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Queue;

public class Exercise2 {

	public static int solve(int floorLength, int floorCount, List<Portal> portals) {
		Grid grid = new Grid(floorLength, floorCount, portals);
		int[] time = new int[grid.getNodesCount()];
		Arrays.fill(time, -1);
		Queue<Integer> queue = new ArrayDeque<>();
		int entryCellId = grid.getEntryCellId();
		time[entryCellId] = 0;
		queue.add(entryCellId);
		int exitCellId = grid.getExitCellId();
		while (!queue.isEmpty() && time[exitCellId] == -1) {
			int current = queue.poll();
			for (int neighbour : grid.getNeighbours(current)) {
				if (time[neighbour] == -1) {
					time[neighbour] = time[current] + 1;
					queue.add(neighbour);
				}
			}
		}

		return time[exitCellId];
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
			String dimensionsStr;
			String portalsStr;
			while ((dimensionsStr = br.readLine()) != null && (portalsStr = br.readLine()) != null) {
				String[] dimensions = dimensionsStr.split(" ");
				int floorLength = Integer.parseInt(dimensions[0]);
				int floorCount = Integer.parseInt(dimensions[1]);

				List<Portal> portals = parsePortals(portalsStr);

				System.out.println(solve(floorLength, floorCount, portals));
			}
		}
	}

	public static List<Portal> parsePortals(String portalsStr) {
		List<Portal> portals = new ArrayList<>();
		String[] portalStrings = portalsStr.split("; ");
		for (String portalString : portalStrings) {
			String[] coordinatesStr = portalString.split(" ");
			int coordinates[] = new int[4];
			for (int i = 0; i < 4; i++) {
				coordinates[i] = Integer.parseInt(coordinatesStr[i]);
			}
			Portal portal = new Portal(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
			portals.add(portal);
		}
		return portals;
	}

}

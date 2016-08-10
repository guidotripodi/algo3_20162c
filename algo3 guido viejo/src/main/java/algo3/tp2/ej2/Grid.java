package algo3.tp2.ej2;

import java.util.ArrayList;
import java.util.List;

public class Grid {

	private final List<List<Integer>> neighbours;
	private final int floorLength;
	private final int floorCount;

	public Grid(int floorLength, int lastFloor, List<Portal> portals) {
		this.floorLength = floorLength + 1;
		this.floorCount = lastFloor + 1;
		neighbours = new ArrayList<>();
		build(portals);
	}

	private void build(List<Portal> portals) {
		for (int floor = 0; floor < floorCount; floor++) {
			for (int distance = 0; distance < floorLength; distance++) {
				List<Integer> cellNeighbours = new ArrayList<Integer>();
				if (distance > 0) {
					cellNeighbours.add(getCellId(floor, distance - 1));
				}
				if (distance < floorLength - 1) {
					cellNeighbours.add(getCellId(floor, distance + 1));
				}
				neighbours.add(cellNeighbours);
			}
		}
		for (Portal portal : portals) {
			int portalId = neighbours.size();
			List<Integer> portalNeighbours = new ArrayList<Integer>();
			int fromId = getCellId(portal.firstFloor, portal.firstDistance);
			int toId = getCellId(portal.secondFloor, portal.secondDistance);
			neighbours.get(fromId).add(portalId);
			neighbours.get(toId).add(portalId);
			portalNeighbours.add(fromId);
			portalNeighbours.add(toId);
			neighbours.add(portalNeighbours);
		}
	}

	public int getNodesCount() {
		return neighbours.size();
	}

	public int getEntryCellId() {
		return getCellId(0, 0);
	}

	public int getExitCellId() {
		return getCellId(floorCount - 1, floorLength - 1);
	}

	public List<Integer> getNeighbours(int cellId) {
		return neighbours.get(cellId);
	}

	private int getCellId(int floor, int distance) {
		return floor * floorLength + distance;
	}

}

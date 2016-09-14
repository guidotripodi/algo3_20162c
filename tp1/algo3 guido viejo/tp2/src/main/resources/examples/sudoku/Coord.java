package uba.algo3.sudoku;

public class Coord {

	int x, y;

	Coord(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public String toString() {
		return "(" + x + "," + y + ")";
	}
}

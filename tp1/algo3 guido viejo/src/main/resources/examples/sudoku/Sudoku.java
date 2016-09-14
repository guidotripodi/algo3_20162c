package uba.algo3.sudoku;

import java.util.ArrayList;
import java.util.List;

public class Sudoku {

	private Board board;
	private List<Coord> holes;

	public Sudoku(Board b) {
		board = b;
	}

	public boolean solve() {
		holes = new ArrayList();

		for (int i = 1; i <= board.side(); ++i)
			for (int j = 1; j <= board.side(); ++j)
				if (board.at(i, j) == 0)
					holes.add(new Coord(i, j));

		return backtrack(0);
	}

	boolean backtrack(int depth) {
		if (depth == holes.size()) {
			return board.valid();
		}

		if (!board.distintos()) {
			return false;
		}

		Coord c = holes.get(depth);

		for (int val : board.workSet()) {
			board.set(c.x, c.y, val);
			if (backtrack(depth + 1)) {
				return true;
			}
		}

		board.set(c.x, c.y, 0);

		return false;
	}

}

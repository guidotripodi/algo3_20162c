package uba.algo3.sudoku;

import static org.junit.Assert.assertTrue;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class SudokuTest {

	long time;

	@Before
	public void before() {
		time = System.currentTimeMillis();
	}

	@After
	public void after() {
		System.out.println(System.currentTimeMillis() - time);
	}

	@Test
	public void vacioTest() {

		Board b = Board.from("0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0");
		assertTrue(new Sudoku(b).solve());
		System.out.println(b);
		assertTrue(b.completo());
		assertTrue(b.distintos());
		assertTrue(b.valid());

	}

	@Test
	public void semiTest() {

		Board b = Board.from("0 2 0 0\n" +
				"0 0 0 2\n" +
				"0 0 0 0\n" +
				"0 0 2 0");
		assertTrue(new Sudoku(b).solve());
		System.out.println(b);
		assertTrue(b.completo());
		assertTrue(b.distintos());
		assertTrue(b.valid());

	}

	@Test
	public void stresTest() {

		Board b;

		for (int i = 0; i < 10000; i++) {
			b = Board.from("0 0 0 0\n" +
					"0 0 0 0\n" +
					"0 0 0 0\n" +
					"0 0 0 0");
			assertTrue(new Sudoku(b).solve());

		}

	}

	@Test
	public void bigTest() {

		Board b = Board.from("0 0 0 0 0 0 0 0 0\n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0 \n" +
				"0 0 0 0 0 0 0 0 0");
		assertTrue(new Sudoku(b).solve());
		System.out.println(b);
		assertTrue(b.completo());
		assertTrue(b.distintos());
		assertTrue(b.valid());

	}
}

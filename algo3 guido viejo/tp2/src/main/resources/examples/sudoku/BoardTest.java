package uba.algo3.sudoku;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;

import org.junit.Test;

import uba.algo3.Utils;

public class BoardTest {

	@Test
	public void dimTest() {

		Board b = Board.from(
				"0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0");
		assertEquals(4, b.side());
		assertEquals(2, b.cuadrante());;

	}

	@Test
	public void vacioTest() {

		Board b = Board.from(
				"0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0\n" +
				"0 0 0 0");
		assertFalse(b.completo());
		assertTrue(b.distintos());
		assertFalse(b.valid());

	}

	@Test
	public void incompletoTest() {

		Board b = Board.from(
				"1 0 3 4\n" +
				"1 2 3 4\n" +
				"1 2 3 4\n" +
				"1 2 3 4");

		assertFalse(b.completo());
		assertFalse(b.distintos());
		assertFalse(b.valid());
	}

	@Test
	public void completoTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"3 4 1 2\n" +
				"2 3 4 1\n" +
				"4 1 2 3");

		assertTrue(b.completo());
		assertTrue(b.distintos());
		assertTrue(b.valid());
	}

	@Test
	public void completoCerosTest() {

		Board b = Board.from(
				"0 2 3 4\n" +
				"3 4 0 2\n" +
				"2 3 4 0\n" +
				"4 0 2 3");

		assertFalse(b.completo());
		assertTrue(b.distintos());
		assertFalse(b.valid());
	}

	@Test
	public void distintosEnLineaTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"1 2 3 4\n" +
				"1 2 3 4\n" +
				"1 2 3 4");

		assertTrue(b.completo());
		assertFalse(b.distintos());
		assertFalse(b.valid());

	}

	@Test
	public void distintosEnColumnasTest() {

		Board b = Board.from(
				"1 1 1 1\n" +
				"2 2 2 2\n" +
				"3 3 3 3\n" +
				"4 4 4 4");

		assertTrue(b.completo());
		assertFalse(b.distintos());
		assertFalse(b.valid());

	}

	@Test
	public void atTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"5 6 7 8\n" +
				"9 0 1 2\n" +
				"3 4 5 6");

		assertEquals(b.at(1, 1), 1);
		assertEquals(b.at(1, 2), 2);
		assertEquals(b.at(1, 3), 3);
		assertEquals(b.at(1, 4), 4);
		assertEquals(b.at(2, 1), 5);
		assertEquals(b.at(2, 2), 6);
		assertEquals(b.at(2, 3), 7);
		assertEquals(b.at(2, 4), 8);
		assertEquals(b.at(3, 1), 9);
		assertEquals(b.at(3, 2), 0);
		assertEquals(b.at(3, 3), 1);
		assertEquals(b.at(3, 4), 2);
		assertEquals(b.at(4, 1), 3);
		assertEquals(b.at(4, 2), 4);
		assertEquals(b.at(4, 3), 5);
		assertEquals(b.at(4, 4), 6);
	}

	@Test
	public void setTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"5 6 7 8\n" +
				"9 0 1 2\n" +
				"3 4 5 6");
		b.set(2, 1, 15);
		b.set(2, 2, 16);
		b.set(2, 3, 17);
		b.set(2, 4, 18);

		assertEquals(15, b.at(2, 1));
		assertEquals(16, b.at(2, 2));
		assertEquals(17, b.at(2, 3));
		assertEquals(18, b.at(2, 4));
	}

	@Test
	public void cuadranteTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"5 6 7 8\n" +
				"9 0 1 2\n" +
				"3 4 5 6");

		assertEquals(Utils.parseVector("1 2 5 6"), b.cuadrante(1, 1));
		assertEquals(Utils.parseVector("3 4 7 8"), b.cuadrante(1, 2));
		assertEquals(Utils.parseVector("9 0 3 4"), b.cuadrante(2, 1));
		assertEquals(Utils.parseVector("1 2 5 6"), b.cuadrante(2, 2));

	}

	@Test
	public void filaTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"5 6 7 8\n" +
				"9 0 1 2\n" +
				"3 4 5 6");

		assertEquals(Utils.parseVector("1 2 3 4"), b.fila(1));
		assertEquals(Utils.parseVector("5 6 7 8"), b.fila(2));
		assertEquals(Utils.parseVector("9 0 1 2"), b.fila(3));
		assertEquals(Utils.parseVector("3 4 5 6"), b.fila(4));

	}

	@Test
	public void columnaTest() {

		Board b = Board.from(
				"1 2 3 4\n" +
				"5 6 7 8\n" +
				"9 0 1 2\n" +
				"3 4 5 6");

		assertEquals(Utils.parseVector("1 5 9 3"), b.columna(1));
		assertEquals(Utils.parseVector("2 6 0 4"), b.columna(2));
		assertEquals(Utils.parseVector("3 7 1 5"), b.columna(3));
		assertEquals(Utils.parseVector("4 8 2 6"), b.columna(4));

	}

}

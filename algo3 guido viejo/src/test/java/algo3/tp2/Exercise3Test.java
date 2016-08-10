package algo3.tp2;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp2.ej3.Exercise3;

public class Exercise3Test {

	@Test
	public void classTest() {
		Assert.assertEquals(3, Exercise3.solve(Exercise3.parseInput("0 1 3; 1 2 3; 2 0 3")));
		Assert.assertEquals(52,
				Exercise3.solve(Exercise3.parseInput("0 1 8; 0 4 70; 0 3 63; 1 2 53; 1 4 54; 2 3 10; 2 4 12; 3 4 22")));
	}
}

package algo3.tp2;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp2.ej1.Exercise1;

public class Exercise1Test {

	@Test
	public void classTest() {
		int lastFloor;
		boolean[][] portals;

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "0 10");
		Assert.assertEquals(Exercise1.solve(portals), 1);

		lastFloor = 9;
		portals = Exercise1.parsePortals(lastFloor, "0 5; 1 6; 2 7; 5 9");
		Assert.assertEquals(Exercise1.solve(portals), 2);

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "0 6; 2 7; 3 8; 6 10");
		Assert.assertEquals(Exercise1.solve(portals), 2);

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "0 3; 3 10; 3 5; 5 6; 6 10");
		Assert.assertEquals(Exercise1.solve(portals), 4);

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "0 1; 1 2; 2 10");
		Assert.assertEquals(Exercise1.solve(portals), 3);

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "2 10; 1 2; 0 1");
		Assert.assertEquals(Exercise1.solve(portals), 3);

		lastFloor = 10;
		portals = Exercise1.parsePortals(lastFloor, "3 8; 6 10; 2 7; 0 6");
		Assert.assertEquals(Exercise1.solve(portals), 2);

	}

}

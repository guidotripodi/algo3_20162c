package algo3.tp2;

import java.util.List;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp2.ej2.Exercise2;
import algo3.tp2.ej2.Portal;

public class Exercise2Test {

	@Test
	public void classTest() {
		int floorLength;
		int floorCount;
		List<Portal> portals;

		floorLength = 10;
		floorCount = 10;
		portals = Exercise2.parsePortals("0 10 10 1");
		Assert.assertEquals(Exercise2.solve(floorLength, floorCount, portals), 21);

		floorLength = 4;
		floorCount = 4;
		portals = Exercise2.parsePortals("0 1 1 2; 1 2 3 1; 2 3 4 0; 3 4 2 1");
		Assert.assertEquals(Exercise2.solve(floorLength, floorCount, portals), 18);

		floorLength = 5;
		floorCount = 5;
		portals = Exercise2.parsePortals("0 2 2 3; 2 4 3 2; 3 1 4 5; 4 3 5 2");
		Assert.assertEquals(Exercise2.solve(floorLength, floorCount, portals), 17);
	}

}

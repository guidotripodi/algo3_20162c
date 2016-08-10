package algo3.tp1;

import java.util.ArrayList;

import java.util.Arrays;
import java.util.List;
import java.util.Random;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp1.ej2.Exercise2;

public class Exercise2Test extends CronometrizedTest {

	@Test
	public void classTest() {
		System.out.println("Running Exercise2 class test");
		Assert.assertEquals(Exercise2.solve(Arrays.asList(2, 3, 4, 1, 2)), Arrays.asList(2, 2, 3, 2, 2));
		Assert.assertEquals(Exercise2.solve(Arrays.asList(2, 7, 2, 8, 4, 9, 1, 6, 5)),
				Arrays.asList(2, 4, 2, 4, 4, 5, 4, 5, 5));
		Assert.assertEquals(Exercise2.solve(Arrays.asList(1, 87, 4)), Arrays.asList(1, 44, 4));
		Assert.assertEquals(Exercise2.solve(Arrays.asList(4, 0, 32, 6, 8, 10)), Arrays.asList(4, 2, 4, 5, 6, 7));
	}

	@Test
	public void complexityTest() {
		System.out.println("Running Exercise2 complexity test");
		for (int size = 1000; size < 100_000; size += 1000) {
			long currentMillis = System.currentTimeMillis();
			Exercise2.solve(randomList(size));
			System.out.println(size + " " + (System.currentTimeMillis() - currentMillis));
		}
	}

	@Test
	public void worstCaseTest() {
		System.out.println("Running Exercise2 worst case test");
		for (int size = 1000; size < 100_000; size += 1000) {
			long sum = 0;
			List<Integer> worstList = getWorstList(size);
			for (int repeat = 0; repeat < 50; repeat++) {
				long startMillis = System.currentTimeMillis();
				Exercise2.solve(worstList);
				sum += System.currentTimeMillis() - startMillis;
			}
			System.out.println(size + " " + (sum / 50));
		}
	}

	private static List<Integer> getWorstList(int size) {
		List<Integer> ret = new ArrayList<>();
		for (int i = 1; i <= size / 2; i++) {
			ret.add(i);
			ret.add(size - i + 1);
		}
		if (size % 2 == 1) {
			ret.add(size / 2 + 1);
		}
		return ret;
	}

	private static List<Integer> randomList(int size) {
		Random rand = new Random();
		List<Integer> randomList = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			randomList.add(rand.nextInt(100_000_000));
		}
		return randomList;
	}

}

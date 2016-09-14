package algo3.tp1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp1.ej1.Exercise1;

public class Exercise1Test extends CronometrizedTest {

	@Test
	public void classTest() {
		System.out.println("Running Exercise1 class test");
		Assert.assertEquals(Exercise1.solve(6, Arrays.asList(6, 8, 12, 15)), 3);
		Assert.assertEquals(Exercise1.solve(35, Arrays.asList(8, 14, 20, 40, 45, 54, 60, 67, 74, 89, 99)), 6);
		Assert.assertEquals(Exercise1.solve(100, Arrays.asList(35, 87, 141, 163, 183, 252, 288, 314, 356, 387)), 4);
		Assert.assertEquals(Exercise1.solve(90, Arrays.asList(6, 8, 16, 19, 28, 32, 37, 45, 52, 60, 69, 78, 82)), 14);
		Assert.assertEquals(Exercise1.solve(4, Arrays.asList(5, 13, 19, 26, 35)), 0);
		Assert.assertEquals(Exercise1.solve(5, Arrays.asList(5, 13, 19, 26, 35)), 2);
		Assert.assertEquals(Exercise1.solve(5, Arrays.asList(7, 16, 19, 27, 33)), 2);
		Assert.assertEquals(Exercise1.solve(8, Arrays.asList(2, 5, 8, 14, 18)), 4);
		Assert.assertEquals(Exercise1.solve(8, Arrays.asList(3, 6, 9, 15, 19)), 3);
	}

	@Test
	public void customTest() {

		System.out.println("Running Exercise1 test");
		Assert.assertEquals(Exercise1.solve(35, Arrays.asList(33, 34, 35, 50, 60, 77, 80, 100, 136)), 5);
		Assert.assertEquals(Exercise1.solve(100, Arrays.asList(40, 50, 60, 77, 80, 99, 100, 120)), 8);
		Assert.assertEquals(Exercise1.solve(90, Arrays.asList(86, 87, 88, 89, 90, 91, 92, 93)), 8);

		Assert.assertEquals(Exercise1.solve(100, Arrays.asList(15, 16, 17, 40, 41, 42, 70, 71, 72, 100,
				101, 102, 140, 141, 142, 170, 171, 172)), 12);
		Assert.assertEquals(Exercise1.solve(50, Arrays.asList(10, 11, 12, 20, 21, 22, 30, 31, 32, 40, 41,
				42, 70, 71, 72)), 13);
		Assert.assertEquals(Exercise1.solve(200, Arrays.asList(15, 16, 17, 40, 41, 42, 70, 71, 72, 100,
				101, 102, 140, 141, 142, 170, 171, 172, 200, 201, 202, 230, 231, 232)), 21);

		// Should return 0
		Assert.assertEquals(Exercise1.solve(10, Arrays.asList(30, 50, 77, 100, 120)), 0);
		Assert.assertEquals(Exercise1.solve(60, Arrays.asList(70, 150, 220, 290, 360, 450)), 0);
		Assert.assertEquals(Exercise1.solve(8, Arrays.asList(10, 20, 30, 40, 50, 59, 69)), 0);

		// Should cover it all
		Assert.assertEquals(Exercise1.solve(30, Arrays.asList(5, 10, 13, 20, 25)), 6);
		Assert.assertEquals(Exercise1.solve(50, Arrays.asList(10, 14, 18, 20, 25, 30)), 7);
		Assert.assertEquals(Exercise1.solve(60, Arrays.asList(10, 20, 30, 40, 50, 55, 58)), 8);

	}

	@Test
	public void bestCaseTest() {
		System.out.println("Running Exercise1 best case test");
		for (int size = 10000; size < 1_000_000; size += 10000) {
			long sum = 0;
			List<Integer> bestList = getbestList(size);
			for (int repeat = 0; repeat < 50; repeat++) {
				long startMillis = System.currentTimeMillis();
				Exercise1.solve(size, bestList);
				sum += System.currentTimeMillis() - startMillis;
			}
			System.out.println(size + " " + (sum / 50));
		}
	}

	@Test
	public void worstCaseTest() {
		System.out.println("Running Exercise1 worst case test");
		for (int size = 10000; size < 1_000_000; size += 10000) {
			long sum = 0;
			List<Integer> worstList = getworstList(size);
			for (int repeat = 0; repeat < 50; repeat++) {
				long startMillis = System.currentTimeMillis();
				Exercise1.solve(size, worstList);
				sum += System.currentTimeMillis() - startMillis;
			}
			System.out.println(size + " " + (sum / 50));
		}
	}

	private static List<Integer> getworstList(int size) {
		List<Integer> ret = new ArrayList<>();
		for (int i = 1; i < size - 2; i++) {
			ret.add((size + 1) * i);
		}
		return ret;
	}

	private static List<Integer> getbestList(int size) {
		List<Integer> ret = new ArrayList<>();
		for (int i = 1; i < size - 2; i++) {
			ret.add(i);
		}
		return ret;
	}

}

package algo3.tp1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.junit.Assert;
import org.junit.Test;

import algo3.tp1.ej3.Exercise3;
import algo3.tp1.ej3.Exercise3.GirlFriendship;
import algo3.tp1.ej3.Exercise3.Result;

public class Exercise3Test extends CronometrizedTest {

	@Test
	public void classTest() {
		System.out.println("Running Exercise3 class test");
		Result result1 = Exercise3.solve(Exercise3.parseFriendships("a bcde;b acde;c abde;d abc;e abc"));
		Assert.assertEquals(result1.getMaxDistance(), 2);
		Assert.assertEquals(result1.getRound(), Arrays.asList('a', 'b', 'd', 'c', 'e'));

		Result result2 = Exercise3.solve(Exercise3.parseFriendships("a bcd;b ae;c ad;d ac;e b"));
		Assert.assertEquals(result2.getMaxDistance(), 2);
		Assert.assertEquals(result2.getRound(), Arrays.asList('a', 'b', 'e', 'c', 'd'));

		Result result3 = Exercise3.solve(Exercise3.parseFriendships("a fb;b gc;d gc;f agh;e hd"));
		Assert.assertEquals(result3.getMaxDistance(), 3);
		Assert.assertEquals(result3.getRound(), Arrays.asList('a', 'b', 'g', 'c', 'd', 'e', 'h', 'f'));

		Result result4 = Exercise3.solve(Exercise3.parseFriendships("x yz"));
		Assert.assertEquals(result4.getMaxDistance(), 1);
		Assert.assertEquals(result4.getRound(), Arrays.asList('x', 'y', 'z'));
	}

	@Test
	public void worstCaseTest() {
		System.out.println("Running Exercise3 worst case test");
		for (int size = 1; size < 13; size++) {
			double sum = 0;
			List<GirlFriendship> worstCase = getWorstCase(size);
			for (int repeat = 0; repeat < 10; repeat++) {
				double startMillis = System.currentTimeMillis();
				Exercise3.solve(worstCase);
				sum += System.currentTimeMillis() - startMillis;
			}
			System.out.println(size + " " + (sum / 10));
		}
	}

	@Test
	public void bestCaseTest() {
		System.out.println("Running Exercise3 best case test");
		for (int size = 100; size < 10000; size += 100) {
			double sum = 0;
			List<GirlFriendship> bestCase = getBestCase(size);
			for (int repeat = 0; repeat < 13; repeat++) {
				double startMillis = System.currentTimeMillis();
				Exercise3.solve(bestCase);
				sum += System.currentTimeMillis() - startMillis;
			}
			System.out.println(size + " " + (sum / 10));
		}
	}

	private static List<GirlFriendship> getBestCase(int size) {
		List<GirlFriendship> friendships = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			char girl = (char) ('a' + i);
			friendships.add(new GirlFriendship(girl, Collections.<Character> emptyList()));
		}
		return friendships;
	}

	private static List<GirlFriendship> getWorstCase(int size) {
		Set<Character> girls = new HashSet<>();
		for (int i = 0; i < size; i++) {
			char girl = (char) ('a' + i);
			girls.add(girl);
		}
		List<GirlFriendship> friendships = new ArrayList<>();
		for (Character girl : girls) {
			Set<Character> others = new HashSet<>(girls);
			others.remove(girl);
			friendships.add(new GirlFriendship(girl, others));
		}
		return friendships;
	}

}

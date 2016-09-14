package algo3.tp1.ej3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;

import algo3.tp1.ej3.Exercise3.Result;

public class BestRoundCalculator {

	private final List<Character> girls;
	private final Set<Friendship> friendships;
	private List<Character> bestRound;
	private int currentMin;
	private int currentSum;
	private int remainingFriendships;

	public BestRoundCalculator(Set<Character> girls, Set<Friendship> friendships) {
		this.girls = new ArrayList<>(girls); // assumes at least one girl
		bestRound = new ArrayList<>(girls);
		this.friendships = friendships;
	}

	public Result calculate() {
		currentSum = 0;
		currentMin = Integer.MAX_VALUE;
		remainingFriendships = friendships.size();
		// Set the first girl at the beginning
		Character firstGirl = Collections.min(girls);
		girls.remove(firstGirl);
		girls.add(0, firstGirl);
		// Backtrack. Start with 1 to avoid circular permutations (ABC-BCA-CAB)
		// We only count the one with the lesser girl at the beginning
		calculate(1);
		return new Result(getMaxDistance(), bestRound);
	}

	private int getMaxDistance() {
		int maxDistance = 0;
		for (int leftIdx = 0; leftIdx < bestRound.size(); leftIdx++) {
			for (int rightIdx = leftIdx; rightIdx < bestRound.size(); rightIdx++) {
				Friendship friendship = new Friendship(bestRound.get(leftIdx), bestRound.get(rightIdx));
				if (friendships.contains(friendship)) {
					maxDistance = Math.max(maxDistance, getDistance(leftIdx, rightIdx));
				}
			}
		}
		return maxDistance;
	}

	private void calculate(int currentIdx) {
		if (remainingFriendships == 0) {
			// 'Remaining friendships' backtrack. If all the friendships were consumed,
			// sort the girls after currentIdx
			// Note that if all the girls are sitting (i.e. currentIdx == girls.size()),
			// then remainingFriendships == 0 must evaluate to true.
			List<Character> sittingGirls = new ArrayList<>(girls);
			// Complexity: k*log(k) with k = girls.size() - currentIdx
			Collections.sort(girls.subList(currentIdx, girls.size()));
			if (currentSum < currentMin) {
				bestRound = sittingGirls;
			} else { // currentSum == currentMin
				bestRound = firstLexicographically(bestRound, sittingGirls);
			}
			currentMin = currentSum;
		} else {
			for (int swapIdx = currentIdx; swapIdx < girls.size(); swapIdx++) {
				Collections.swap(girls, currentIdx, swapIdx);
				CountSumDistance countSum = getPartialDistance(currentIdx);
				currentSum += countSum.getSum();
				remainingFriendships -= countSum.getCount();
				// Partial distance backtrack. If the current sum is not better than the
				// current minimum, drop the candidate and keep going
				if (currentSum <= currentMin) {
					calculate(currentIdx + 1);
				}
				Collections.swap(girls, currentIdx, swapIdx);
				currentSum -= countSum.getSum();
				remainingFriendships += countSum.getCount();
			}
		}
	}

	private CountSumDistance getPartialDistance(int currentIdx) {
		int sum = 0;
		int count = 0;
		for (int girlIdx = 0; girlIdx < currentIdx; girlIdx++) {
			Friendship friendship = new Friendship(girls.get(girlIdx), girls.get(currentIdx));
			if (friendships.contains(friendship)) {
				sum += getDistance(girlIdx, currentIdx);
				count++;
			}
		}
		return new CountSumDistance(count, sum);
	}

	private int getDistance(int leftIdx, int rightIdx) {
		return Math.min(rightIdx - leftIdx, girls.size() - (rightIdx - leftIdx));
	}

	private static List<Character> firstLexicographically(List<Character> first, List<Character> second) {
		for (int i = 0; i < first.size(); i++) {
			int compared = first.get(i).compareTo(second.get(i));
			if (compared < 0) {
				return first;
			} else if (compared > 0) {
				return second;
			}
		}
		return first;
	}

	private static class CountSumDistance {

		private final int sum;
		private final int count;

		public CountSumDistance(int count, int sum) {
			this.count = count;
			this.sum = sum;
		}

		public int getCount() {
			return count;
		}

		public int getSum() {
			return sum;
		}

	}

}

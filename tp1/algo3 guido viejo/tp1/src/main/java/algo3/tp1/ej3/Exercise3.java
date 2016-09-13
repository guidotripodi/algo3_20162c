package algo3.tp1.ej3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import algo3.Utils;

public class Exercise3 {

	public static Result solve(List<GirlFriendship> girlFriendships) {
		if (girlFriendships == null) {
			throw new IllegalArgumentException();
		}
		Set<Character> girls = new TreeSet<>();
		Set<Friendship> friendships = new TreeSet<>();
		for (GirlFriendship girlFriendship : girlFriendships) {
			char girl = girlFriendship.getGirl();
			girls.add(girl);
			for (char friend : girlFriendship.getFriends()) {
				friendships.add(new Friendship(girl, friend));
				girls.add(friend);
			}
		}
		BestRoundCalculator bestRoundCalculator = new BestRoundCalculator(girls, friendships);
		return bestRoundCalculator.calculate();
	}

	/**
	 * Parse input of the form 'a fb;b gc;d gc;f agh'
	 */
	public static List<GirlFriendship> parseFriendships(String friendshipsStr) {
		String[] friendshipArray = friendshipsStr.split(";");
		List<GirlFriendship> friendships = new ArrayList<>(friendshipArray.length);
		for (int i = 0; i < friendshipArray.length; i++) {
			String friendshipStr = friendshipArray[i];
			String[] split = friendshipStr.split(" ");
			char girl = split[0].charAt(0);
			List<Character> friends = new ArrayList<>();
			if (split.length == 2) { // there is friends present
				String friendsStr = split[1];
				for (int j = 0; j < friendsStr.length(); j++) {
					friends.add(friendsStr.charAt(j));
				}
			}
			friendships.add(new GirlFriendship(girl, friends));
		}
		System.out.println(friendships);
		return friendships;
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
			String inputStr;
			while ((inputStr = br.readLine()) != null) {
				System.out.println(solve(parseFriendships(inputStr)));
			}
		}
	}

	public static class GirlFriendship {

		private final char girl;
		private final Set<Character> friends;

		public GirlFriendship(char girl, Collection<Character> friends) {
			this.girl = girl;
			this.friends = new TreeSet<>(friends);
		}

		public char getGirl() {
			return girl;
		}

		public Set<Character> getFriends() {
			return friends;
		}

		@Override
		public String toString() {
			return "GirlFriendship [girl=" + girl + ", friends=" + friends + "]";
		}

	}

	public static class Result {

		private final int maxDistance;
		private final List<Character> round;

		public Result(int maxDistance, List<Character> round) {
			this.maxDistance = maxDistance;
			this.round = round;
		}

		public int getMaxDistance() {
			return maxDistance;
		}

		public List<Character> getRound() {
			return round;
		}

		@Override
		public String toString() {
			return maxDistance + " " + Utils.join(round, "");
		}

	}

}

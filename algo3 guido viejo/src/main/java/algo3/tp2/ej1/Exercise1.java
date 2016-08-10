package algo3.tp2.ej1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Exercise1 {

	public static int solve(boolean[][] portals) {

		int[] maxiPortalsPath = new int[portals.length];
		Arrays.fill(maxiPortalsPath, Integer.MIN_VALUE);
		maxiPortalsPath[0] = 0;
		for (int i = 1; i < maxiPortalsPath.length; i++) {
			for (int j = 0; j < i; j++) {
				if (portals[j][i]) {
					maxiPortalsPath[i] = Math.max(maxiPortalsPath[i], maxiPortalsPath[j] + 1);
				}
			}
		}
		return maxiPortalsPath[maxiPortalsPath.length - 1];
	}

	/**
	 * Parse string of the form '0 5; 1 6; 2 7'
	 * 
	 * @return ret[i][j] is true iff there is a portal between floors i and j
	 */
	public static boolean[][] parsePortals(int lastFloor, String portalsStr) {
		boolean[][] portals = new boolean[lastFloor + 1][lastFloor + 1];
		String[] splittedPortals = portalsStr.split("; ");
		for (int i = 0; i < splittedPortals.length; i++) {
			String[] floors = splittedPortals[i].split(" ");
			int to = Integer.parseInt(floors[0]);
			int from = Integer.parseInt(floors[1]);
			portals[to][from] = true;
		}
		return portals;
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int lastFloor = Integer.parseInt(br.readLine());
		boolean[][] portals = parsePortals(lastFloor, br.readLine());
		System.out.println(solve(portals));
	}
}

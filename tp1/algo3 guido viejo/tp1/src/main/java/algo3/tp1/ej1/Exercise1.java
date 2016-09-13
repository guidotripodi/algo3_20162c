package algo3.tp1.ej1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Exercise1 {

	public static int solve(int cableSize, List<Integer> stationDistances) {
		if (cableSize < 0 || stationDistances == null) {
			throw new IllegalArgumentException();
		}
		List<Integer> distanceDifferences = new ArrayList<>(stationDistances.size());
		int lastStation = 0;
		for (int distance : stationDistances) {
			distanceDifferences.add(distance - lastStation);
			lastStation = distance;
		}
		int maxRangeLength = getMaxRangeLength(cableSize, distanceDifferences);
		return maxRangeLength == 0 ? 0 : maxRangeLength + 1;
	}

	private static int getMaxRangeLength(int cableSize, List<Integer> distanceDifferences) {
		int ret = 0;
		int rangeSize = 0;
		int sum = 0;
		Iterator<Integer> leftIter = distanceDifferences.iterator();
		for (int distance : distanceDifferences) {
			sum += distance;
			rangeSize++;
			while (sum > cableSize) {
				rangeSize--;
				sum -= leftIter.next();
			}
			ret = Math.max(ret, rangeSize);
		}
		return ret;
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
			String cableSizeStr;
			String stationsStr;
			while ((cableSizeStr = br.readLine()) != null && (stationsStr = br.readLine()) != null) {
				int cableSize = Integer.parseInt(cableSizeStr);
				String[] split = stationsStr.split(" ");
				List<Integer> stationDistances = new ArrayList<>(split.length);
				for (int i = 0; i < split.length; i++) {
					stationDistances.add(Integer.parseInt(split[i]));
				}
				System.out.println(solve(cableSize, stationDistances));
			}
		}
	}
}

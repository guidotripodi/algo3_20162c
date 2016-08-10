package algo3.tp1.ej2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import algo3.Utils;

public class Exercise2 {

	public static List<Integer> solve(List<Integer> numbers) {
		if (numbers == null) {
			throw new IllegalArgumentException();
		}
		List<Integer> ret = new ArrayList<>(numbers.size());
		HeapMedianCalculator medianCalculator = new HeapMedianCalculator(numbers.size());
		for (int number : numbers) {
			medianCalculator.add(number);
			ret.add(medianCalculator.getMedian());
		}
		return ret;
	}

	public static void main(String[] args) throws IOException {
		System.out.println(Integer.MAX_VALUE);
		try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
			String numbersStr;
			while ((numbersStr = br.readLine()) != null) {
				String[] split = numbersStr.split(" ");
				List<Integer> numbers = new ArrayList<>(split.length);
				for (int i = 0; i < split.length; i++) {
					numbers.add(Integer.parseInt(split[i]));
				}
				System.out.println(Utils.join(solve(numbers), " "));
			}
		}
	}

}

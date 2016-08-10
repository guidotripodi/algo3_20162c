package algo3.tp1.ej2;

import java.util.Collections;
import java.util.PriorityQueue;

public class HeapMedianCalculator {

	private final PriorityQueue<Integer> lowerHalf;
	private final PriorityQueue<Integer> greaterHalf;

	public HeapMedianCalculator(int maxSize) {
		lowerHalf = new PriorityQueue<>(maxSize / 2 + 1, Collections.reverseOrder());
		greaterHalf = new PriorityQueue<>(maxSize / 2 + 1);
	}

	/**
	 * Returns the median of the contained values
	 * Assumes there is no two elements such that their sum is greater than Integer.MAX_VALUE (2^31 - 1)
	 * 
	 * @return the median of the contained values, or null if no values
	 */
	public Integer getMedian() {
		int currentSize = size();
		if (currentSize == 0) {
			return null;
		} else if (currentSize % 2 == 0) {
			return (greaterHalf.peek() + lowerHalf.peek()) / 2;
		} else {
			return lowerHalf.peek();
		}
	}

	public void add(int element) {
		if (size() % 2 == 0) {
			greaterHalf.add(element);
			lowerHalf.add(greaterHalf.poll());
		} else {
			lowerHalf.add(element);
			greaterHalf.add(lowerHalf.poll());
		}
	}

	private int size() {
		return lowerHalf.size() + greaterHalf.size();
	}
}

package algo3.tp3;

import java.util.Set;
import java.util.SortedMap;
import java.util.SortedSet;
import java.util.TreeMap;
import java.util.TreeSet;

public class ValueSortedMap<K, V> {

	private final SortedMap<K, V> normalMap;
	private final SortedMap<V, SortedSet<K>> invertedMap;

	public ValueSortedMap() {
		normalMap = new TreeMap<>();
		invertedMap = new TreeMap<>();
	}

	public void put(K key, V value) {
		V currentValue = normalMap.get(key);
		if (currentValue != null) {
			Set<K> valueKeys = invertedMap.get(currentValue);
			valueKeys.remove(key);
			if (valueKeys.isEmpty())
				invertedMap.remove(currentValue);
		}

		normalMap.put(key, value);
		SortedSet<K> newValueKeys = invertedMap.get(value);
		if (newValueKeys == null) {
			newValueKeys = new TreeSet<>();
			invertedMap.put(value, newValueKeys);
		}
		newValueKeys.add(key);
	}

	public boolean isEmpty() {
		return normalMap.isEmpty();
	}

	public V getMinValue() {
		return invertedMap.firstKey();
	}

	public V getMaxValue() {
		return invertedMap.lastKey();
	}

	public K popMinValueKey() {
		V minValue = getMinValue();
		SortedSet<K> minValueKeys = invertedMap.get(minValue);
		K minKey = minValueKeys.first();
		minValueKeys.remove(minKey);
		if (minValueKeys.isEmpty()) {
			invertedMap.remove(minValue);
		}
		normalMap.remove(minKey);
		return minKey;
	}

	public K popMaxValueKey() {
		V maxValue = getMaxValue();
		SortedSet<K> maxValueKeys = invertedMap.get(maxValue);
		K maxKey = maxValueKeys.last();
		maxValueKeys.remove(maxKey);
		if (maxValueKeys.isEmpty()) {
			invertedMap.remove(maxValue);
		}
		normalMap.remove(maxKey);
		return maxKey;
	}

}

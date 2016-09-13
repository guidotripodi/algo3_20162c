package algo3.tp2.ej3;

public class Corridor implements Comparable<Corridor> {

	private final int firstIntersection;
	private final int secondIntersection;
	private final int length;

	public Corridor(int firstIntersection, int secondIntersection, int lenght) {
		this.firstIntersection = firstIntersection;
		this.secondIntersection = secondIntersection;
		this.length = lenght;
	}

	public int getFirstIntersection() {
		return firstIntersection;
	}

	public int getSecondIntersection() {
		return secondIntersection;
	}

	public int getLength() {
		return length;
	}

	@Override
	public int compareTo(Corridor o) {
		return length - o.length;
	}
}

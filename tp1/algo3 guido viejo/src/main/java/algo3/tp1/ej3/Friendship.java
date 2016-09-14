package algo3.tp1.ej3;

public class Friendship implements Comparable<Friendship> {

	private final char first;
	private final char second;

	public Friendship(char first, char second) {
		// Given that the friendship is a symmetrical relationship,
		// we are able to save the friendships keeping first <= second
		this.first = first < second ? first : second;
		this.second = first > second ? first : second;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + first;
		result = prime * result + second;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) return true;
		if (obj == null) return false;
		if (getClass() != obj.getClass()) return false;
		Friendship other = (Friendship) obj;
		if (first != other.first) return false;
		if (second != other.second) return false;
		return true;
	}

	@Override
	public int compareTo(Friendship o) {
		int compare = Character.compare(this.first, o.first);
		return compare != 0 ? compare : Character.compare(this.second, o.second);
	}

	public char getFirst() {
		return first;
	}

	public char getSecond() {
		return second;
	}

	@Override
	public String toString() {
		return "Friendship [first=" + first + ", second=" + second + "]";
	}

}

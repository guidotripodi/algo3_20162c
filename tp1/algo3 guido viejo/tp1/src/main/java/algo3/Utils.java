package algo3;

import java.util.List;

public class Utils {

	public static <T> String join(List<T> objects, String separator) {
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < objects.size(); i++) {
			stringBuilder.append(objects.get(i).toString());
			if (i != objects.size() - 1) {
				stringBuilder.append(separator);
			}
		}
		return stringBuilder.toString();
	}

}

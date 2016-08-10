package algo3.tp1;

import org.junit.After;
import org.junit.Before;

public class CronometrizedTest {

	long time;

	@Before
	public void before() {
		time = System.currentTimeMillis();
	}

	@After
	public void after() {
		System.out.println("Milliseconds elapsed : " + (System.currentTimeMillis() - time));
	}

}

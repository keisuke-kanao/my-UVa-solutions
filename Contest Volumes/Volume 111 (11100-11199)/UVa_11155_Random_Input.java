
import java.util.Random;

class Main {
	public static void main(String[] args) {
		final int t = 500, aMax = 1000, nMax = 10000;
		Random rand = new Random();
		System.out.printf("%d\n", t);
		for (int i = 0; i < t; i++)
			System.out.printf("%d %d %d %d %d\n", 
				rand.nextInt(aMax), rand.nextInt(aMax), rand.nextInt(aMax),
				rand.nextInt(nMax) + 1, rand.nextInt(nMax) + 1);
	}
}


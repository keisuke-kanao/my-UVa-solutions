
import java.util.Random;

class Main {
	public static void main(String[] args) {
		final int t = 100, nMax = 1000, nrMax = 20000;
		Random rand = new Random();
		System.out.printf("%d\n", t);
		for (int i = 0; i < t; i++) {
			System.out.println();
			int n = rand.nextInt(nMax) + 1, k = rand.nextInt(nMax) + 1;
			System.out.printf("%d %d\n", k, n);
			for (int j = 0; j < n; j++)
				System.out.printf("%d %d\n", rand.nextInt(nrMax) - nrMax / 2, rand.nextInt(nrMax) - nrMax / 2);
		}
	}
}


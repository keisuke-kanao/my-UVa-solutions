
import java.util.Random;

class Main {
	public static void main(String[] args) {
		final int t = 10000, nMax = 100, xyMax = 10;
		Random rand = new Random();
		System.out.printf("%d\n", t);
		for (int i = 0; i < t; i++) {
			int n = rand.nextInt(nMax) + 1;
			System.out.printf("%d\n", n);
			for (int j = 0; j < n; j++)
				System.out.printf("%d %d\n", rand.nextInt(xyMax) - xyMax / 2, rand.nextInt(nMax) - xyMax / 2);
		}
	}
}


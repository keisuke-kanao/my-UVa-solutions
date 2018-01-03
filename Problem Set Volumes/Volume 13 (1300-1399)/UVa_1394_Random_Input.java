
import java.util.Random;

class Main {
	public static void main(String[] args) {
		final int t = 100, nMax = 10000, kMax = 10000;
		Random rand = new Random();
		for (int i = 0; i < t; i++) {
			int n, k, m;
			do
				n = rand.nextInt(nMax) + 1;
			while (n == 1);
			k = rand.nextInt(kMax) + 1;
			m = rand.nextInt(n) + 1;
			System.out.printf("%d %d %d\n", n, k, m);
		}
		System.out.println("0 0 0");
	}
}


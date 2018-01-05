
import java.util.Random;

class Main {
	public static void main(String[] args) {
		final int t = 1000, nMax = 45;
		Random rand = new Random();
		for (int i = 0; i < t; i++) {
			int a1 = rand.nextInt(nMax), an = rand.nextInt(nMax);
			if (a1 > an)
				System.out.printf("%d %d\n", an, a1);
			else
				System.out.printf("%d %d\n", a1, an);
		}
		System.out.println("0 0");
	}
}


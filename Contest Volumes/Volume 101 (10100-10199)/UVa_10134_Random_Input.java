
import java.util.Random;

class Main {
	public static void main(String[] args) {
		int t = 100, nMax = 100;
		Random rand = new Random();
		System.out.printf("%d\n\n", t);
		while (t-- > 0) {
			int n = rand.nextInt(nMax) + 1;
			while (n-- > 0) {
				switch (rand.nextInt(3)) {
				case 0:
					System.out.println("fish"); break;
				case 1:
					System.out.println("bait"); break;
				default:
					System.out.println("lunch"); break;
				}
			}
			if (t > 0)
				System.out.println();
		}
	}
}


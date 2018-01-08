
// UVa 568 - Just the Facts
// Another accepted solution.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final int n_max = 10000;

	public static void main(String[] args) {
//		long start = System.currentTimeMillis();
		int[] cache = new int[n_max + 1];
		calculateLastNonZeroDigitOfFactorials(cache);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			System.out.println(String.format("%5d -> %d", n, cache[n]));
		}
//		System.err.println("elapsed time = " + (System.currentTimeMillis() - start) + " milliseconds");
	}

	static void calculateLastNonZeroDigitOfFactorials(int [] cache)
	{
		cache[0] = cache[1] = 1;
		BigInteger f = BigInteger.ONE;
		for (int i = 2; i <= n_max; i++) {
			int j = i;
			while (true) {
				if ((j % 10) != 0)
					break;
				j /= 10;
			}
			f = f.multiply(BigInteger.valueOf(j));
			while (true) {
				int remainder = f.mod(BigInteger.TEN).intValue();
				if (remainder != 0) {
					cache[i] = remainder;
					break;
				}
				f = f.divide(BigInteger.TEN);
			}
		}
	}
}


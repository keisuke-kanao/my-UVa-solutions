
/*
	6.6.6 The Priest Mathematician
	PC/UVa IDs: 110606/10254, Popularity: C, Success rate: high Level: 2
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int n_max = 10000;
		final BigInteger BI2 = BigInteger.valueOf(2);
		BigInteger f[] = new BigInteger[n_max + 1]; // for the standard three needles strategy
		BigInteger g[] = new BigInteger[n_max + 1]; // for the four needles strategy
		f[0] = g[0] = BigInteger.ZERO;
		int min_j = 0;
		for (int i = 1; i <= n_max; i++) {
			f[i] = BI2.multiply(f[i - 1]).add(BigInteger.ONE);
			int j = min_j;
			BigInteger min_gi = BI2.multiply(g[j]).add(f[i - j]);
			if (j > 0) {
				BigInteger gi = BI2.multiply(g[j - 1]).add(f[i - j + 1]);
				if (gi.compareTo(min_gi) == -1) {
					min_j = j - 1; min_gi = gi;
				}
			}
			if (j < i - 1) {
				BigInteger gi = BI2.multiply(g[j + 1]).add(f[i - j - 1]);
				if (gi.compareTo(min_gi) == -1) {
					min_j = j + 1; min_gi = gi;
				}
			}
			g[i] = min_gi;
		}

		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			System.out.println(g[n]);
		}
	}
}


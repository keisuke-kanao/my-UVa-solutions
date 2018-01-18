
/*
	6.6.4 Expressions
	PC/UVa IDs: 110604/10157, Popularity: C, Success rate: average Level: 2
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int parenthesesMax = 150, depthMax = 150;
		BigInteger[][] cache = new BigInteger[parenthesesMax + 1][depthMax + 1];
		countExpressions(parenthesesMax, depthMax, cache);

		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt() / 2;
			if (sc.hasNextInt()) {
				int d = sc.nextInt();
				System.out.println(cache[n][d].subtract(cache[n][d - 1]));
			}
		}
	}

	static void countExpressions(int nMax, int dMax, BigInteger[][] cache) {
		for (int j = 0; j <= dMax; j++)
			cache[0][j] = BigInteger.ONE;
		for (int i = 1; i <= nMax; i++)
			cache[i][0] = BigInteger.ZERO;
		for (int i = 1; i <= nMax; i++)
			for (int j = 1; j <= dMax; j++) {
				BigInteger cn = BigInteger.ZERO;
				for (int k = 0; k < i; k++)
					cn = cn.add(cache[k][j - 1].multiply(cache[i - k - 1][j]));
				cache[i][j] = cn;
			}
	}
}


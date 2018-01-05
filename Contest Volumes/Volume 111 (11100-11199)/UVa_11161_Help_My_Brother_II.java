
// UVa 11161 - Help My Brother (II)

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 1500;
		final BigInteger TWO = BigInteger.valueOf(2);
		BigInteger[] fibs = new BigInteger[nMax + 1], totals = new BigInteger[nMax + 1];
		fibs[1] = fibs[2] = BigInteger.ONE;
		totals[1] = BigInteger.ZERO;
		totals[2] = BigInteger.ONE;
		for (int i = 3; i <= nMax; i++) {
			fibs[i] = fibs[i - 1].add(fibs[i - 2]);
			totals[i] = totals[i - 1].add(fibs[i - 1]);
		}
		Scanner sc = new Scanner(System.in);
		for (int s = 1; ; s++) {
			int n = sc.nextInt();
			if (n == 0)
				break;
			System.out.printf("Set %d:\n", s);
			if (fibs[n].mod(TWO).equals(BigInteger.ONE)) // number of elements is odd
				System.out.println(fibs[n].add(BigInteger.ONE).divide(TWO).subtract(BigInteger.ONE).add(totals[n]));
			else // number of elements is even
				System.out.println(fibs[n].divide(TWO).subtract(BigInteger.ONE).add(totals[n]));
		}
	}
}


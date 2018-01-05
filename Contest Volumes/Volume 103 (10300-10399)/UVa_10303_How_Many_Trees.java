
// UVa 10303 - How Many Trees?

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
/*
		long start = System.currentTimeMillis();
*/
		final int nMax = 1000;
		final BigInteger TWO = BigInteger.valueOf(2);
		BigInteger[] catalanNumbers = new BigInteger[nMax + 1];
		catalanNumbers[0] = BigInteger.ONE;
		for (int i = 1; i <= nMax; i++)
			catalanNumbers[i] =
				catalanNumbers[i - 1].multiply(BigInteger.valueOf(4 * i - 2)).divide(BigInteger.valueOf(i + 1));
/*
		System.out.println(catalanNumbers[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt())
			System.out.println(catalanNumbers[sc.nextInt()]);
/*
		System.err.println("elapsed time = " + (System.currentTimeMillis() - start) + " milliseconds");
*/
	}
}


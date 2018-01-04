
// UVa 11448 - Who said crisis?

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
/*
		long start = System.currentTimeMillis();
*/
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while (t-- > 0) {
			BigInteger a = sc.nextBigInteger(), b = sc.nextBigInteger();
			System.out.println(a.subtract(b));
		}
/*
		System.err.println("elapsed time = " + (System.currentTimeMillis() - start) + " milliseconds");
*/
	}
}


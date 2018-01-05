
// UVa 10519 - !! Really Strange !!

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final BigInteger TWO = BigInteger.valueOf(2);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextBigInteger()) {
			BigInteger n = sc.nextBigInteger();
			if (n.compareTo(BigInteger.ZERO) == 0)
				System.out.println(BigInteger.ONE);
			else // f(n) = n * (n - 1) + 2
				System.out.println(n.subtract(BigInteger.ONE).multiply(n).add(TWO));
		}
	}
}


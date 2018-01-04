
// 	UVa 11879 - Multiple of 17

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final BigInteger FIVE = BigInteger.valueOf(5), SEVENTEEN = BigInteger.valueOf(17);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextBigInteger()) {
			BigInteger n = sc.nextBigInteger();
			if (n.compareTo(BigInteger.ZERO) == 0)
				break;
			BigInteger d = n.mod(BigInteger.TEN);
			n = n.divide(BigInteger.TEN).subtract(d.multiply(FIVE)); // n / 10 - 5 * d
			BigInteger r = n.remainder(SEVENTEEN);
			System.out.println((r.compareTo(BigInteger.ZERO) == 0) ? 1 : 0);
		}
	}
}


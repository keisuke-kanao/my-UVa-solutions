
/*
	6.6.2 How Many Pieces of Land?
	PC/UVa IDs: 110602/10213, Popularity: B, Success rate: average Level: 2
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	private static final BigInteger BI24 = BigInteger.valueOf(24), BI6 = BigInteger.valueOf(6),
		BI23 = BigInteger.valueOf(23), BI18 = BigInteger.valueOf(18);

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		try {
			int n = sc.nextInt(); // number of input instances
			while (n-- != 0) {
				System.out.println(howManyPiecesOfLand(sc.nextInt()));
			}
		}
		catch (RuntimeException e) { // NoSuchElementException (or IllegalStateException)
		}
	}

	static BigInteger howManyPiecesOfLand(int i) {
		BigInteger n = BigInteger.valueOf(i);
		if (n.equals(BigInteger.ZERO))
			return BigInteger.ONE;
		else {
			// (n^4 - 6 * n^3 + 23 * n^2 - 18 * n) / 24 + 1
			BigInteger fourthTerm = n.pow(4), thirdTerm = n.pow(3).multiply(BI6),
				secondTerm = n.pow(2).multiply(BI23), firstTerm = n.multiply(BI18);
			return fourthTerm.subtract(thirdTerm).add(secondTerm).subtract(firstTerm).divide(BI24).add(BigInteger.ONE);
		}
	}
}


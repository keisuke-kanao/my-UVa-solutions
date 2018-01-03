
/*
	UVa 619 - Numerically Speaking

	from ACM North Central Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/index.html)
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final BigInteger TWENTY_SIX = BigInteger.valueOf(26);

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			if (sc.hasNextBigInteger()) {
				BigInteger n = sc.nextBigInteger();
				String s = convertToString(n);
				System.out.printf("%-22s%s%n", s, getNumberToBePrinted(n));
			}
			else if (sc.hasNext()) {
				String s = sc.next();
				if (s.equals("*"))
					break;
				BigInteger n = convertToNumber(s);
				System.out.printf("%-22s%s%n", s, getNumberToBePrinted(n));
			}
		}
	}

	static String convertToString(BigInteger n) {
		StringBuilder sb = new StringBuilder();
		do {
			sb.append((char)('a' + n.subtract(BigInteger.ONE).mod(TWENTY_SIX).intValue()));
			n = n.subtract(BigInteger.ONE).divide(TWENTY_SIX);
		} while (n.compareTo(BigInteger.ZERO) != 0);
		sb.reverse();
		return sb.toString();
	}

	static BigInteger convertToNumber(String s) {
		BigInteger n = BigInteger.ZERO;
		for (int i = 0; i < s.length(); i++) {
			n = n.multiply(TWENTY_SIX);
			n = n.add(BigInteger.valueOf((int)(s.charAt(i) - 'a' + 1)));
		}
		return n;
	}

	static String getNumberToBePrinted(BigInteger n) {
		String s = n.toString();
		StringBuilder sb = new StringBuilder();
		for (int i = s.length() - 1, j = 0; i >= 0; i--, j++) {
			sb.append(s.charAt(i));
			if (i > 0 && (j % 3) == 2)
				sb.append(',');
		}
		sb.reverse();
		return sb.toString();
	}
}


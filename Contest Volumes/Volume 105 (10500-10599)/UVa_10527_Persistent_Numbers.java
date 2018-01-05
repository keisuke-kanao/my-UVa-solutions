
/*
	UVa 10527 - Persistent Numbers

	from Waterloo ACM Programming Contest, July 5, 2003, Problem B
		(http://acm.student.cs.uwaterloo.ca/~acm00/030920/data/)
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final BigInteger TWO = BigInteger.valueOf(2), THREE = BigInteger.valueOf(3),
		FIVE = BigInteger.valueOf(5), SEVEN = BigInteger.valueOf(7);

	public static void main(String[] args) {
		final BigInteger MINUSONE = BigInteger.valueOf(-1);
		int[] numberOfFactors = new int[9 - 0 + 1];
			// numberOfFactors[i] is the number of prime factors for i
	    Scanner sc = new Scanner(System.in);
		while (true) {
			BigInteger n = sc.nextBigInteger();
			if (n.equals(MINUSONE))
				break;
			else if (n.equals(BigInteger.ZERO))
				System.out.println("10");
			else if (n.equals(BigInteger.ONE))
				System.out.println("11");
			else if (getNumberOfPrimeFactors(n, numberOfFactors)) {
				StringBuilder sb = new StringBuilder();
				while (true) {
					int d = getNextDidit(numberOfFactors);
					if (d == 0)
						break;
					sb.append((char)(d + '0'));
				}
				if (sb.length() == 1)
					sb.append('1');
				sb.reverse();
				System.out.println(sb);
			}
			else
				System.out.println("There is no such number.");
		}
	}

	static boolean getNumberOfPrimeFactors(BigInteger n, int[] numberOfFactors) {
		numberOfFactors[2] = numberOfFactors[3] = numberOfFactors[5] = numberOfFactors[7] = 0;
		while (n.mod(TWO).equals(BigInteger.ZERO)) {
			numberOfFactors[2]++;
			n = n.divide(TWO);
		}
		while (n.mod(THREE).equals(BigInteger.ZERO)) {
			numberOfFactors[3]++;
			n = n.divide(THREE);
		}
		while (n.mod(FIVE).equals(BigInteger.ZERO)) {
			numberOfFactors[5]++;
			n = n.divide(FIVE);
		}
		while (n.mod(SEVEN).equals(BigInteger.ZERO)) {
			numberOfFactors[7]++;
			n = n.divide(SEVEN);
		}
		return n.equals(BigInteger.ONE);
	}

	static int getNextDidit(int[] numberOfFactors) {
		if (numberOfFactors[3] >= 2) {
			numberOfFactors[3] -= 2; return 9;
		}
		else if (numberOfFactors[2] >= 3) {
			numberOfFactors[2] -= 3; return 8;
		}
		else if (numberOfFactors[7] != 0) {
			numberOfFactors[7]--; return 7;
		}
		else if (numberOfFactors[2] != 0 && numberOfFactors[3] != 0) {
			numberOfFactors[2]--; numberOfFactors[3]--; return 6;
		}
		else if (numberOfFactors[5] != 0) {
			numberOfFactors[5]--; return 5;
		}
		else if (numberOfFactors[2] >= 2) {
			numberOfFactors[2] -= 2; return 4;
		}
		else if (numberOfFactors[3] != 0) {
			numberOfFactors[3]--; return 3;
		}
		else if (numberOfFactors[2] != 0) {
			numberOfFactors[2]--; return 2;
		}
		else
			return 0;
	}
}



// UVa 787 - Maximum Sub-sequence Product

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final int iMin = -999999, nMax = 100;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int[] sequence = new int[nMax];
			int n = 0, i = sc.nextInt();
			do {
				sequence[n++] = i;
				i = sc.nextInt();
			} while (i != iMin);
			System.out.println(maxSubsequenceProduct(n, sequence));
		}
	}

	static BigInteger maxSubsequenceProduct(int n, int[] sequence) {
		boolean zero = false;
		BigInteger maxP = BigInteger.valueOf(iMin);
		int i = 0;
		while (i < n) {
			for ( ;i < n && sequence[i] == 0; i++)
				zero = true;
			int j = i;
			for ( ; j < n && sequence[j] != 0; j++)
				;
			if (i < j) {
				maxP = maxP.max(maxProductNonZero(sequence, i, j));
				i = j;
			}
		}
		if (zero)
			maxP = maxP.max(BigInteger.ZERO);
		return maxP;
	}

	static BigInteger maxProductNonZero(int[] sequence, int a, int b) { // calculate the product of non-zero sequence [a, b)
		if (a + 1 == b) // only one item
			return BigInteger.valueOf(sequence[a]);
		int iFirstNegative = -1, iLastNegative = -1, nrNegatives = 0;
		for (int i = a; i < b; i++)
			if (sequence[i] < 0) {
				nrNegatives++;
				if (iFirstNegative < 0)
					iFirstNegative = i;
				iLastNegative = i;
			}
		if (nrNegatives % 2 == 0)
			return calculateProduct(sequence, a, b);
		else
			return calculateProduct(sequence, iFirstNegative + 1, b).max(calculateProduct(sequence, a, iLastNegative));
	}

	static BigInteger calculateProduct(int[] sequence, int a, int b) { // calculate the product of sequence [a, b)
		BigInteger p = BigInteger.ONE;
		for (int i = a; i < b; i++)
			p = p.multiply(BigInteger.valueOf(sequence[i]));
		return p;
	}
}


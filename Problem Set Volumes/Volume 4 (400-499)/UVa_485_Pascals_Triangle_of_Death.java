
// UVa 485 - Pascal's Triangle of Death

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 256;
		BigInteger[][] binomialCoefficients = new BigInteger[2][nMax + 1];
		binomialCoefficients[0][1] = binomialCoefficients[1][1] = BigInteger.ONE;
		final BigInteger bcMax = BigInteger.valueOf(10).pow(60);
		boolean exit = false;
		for (int i = 1; i <= nMax && !exit; i++) {
			BigInteger[] pbc, cbc;
			if ((i & 1) != 0) {
				pbc = binomialCoefficients[0]; cbc = binomialCoefficients[1];
			}
			else {
				pbc = binomialCoefficients[1]; cbc = binomialCoefficients[0];
			}
			for (int j = 2; j < i; j++) {
				cbc[j] = pbc[j - 1].add(pbc[j]);
				if (cbc[j].compareTo(bcMax) >= 0)
					exit = true;
			}
			cbc[i] = BigInteger.ONE;
			for (int j = 1; j <= i; j++) {
				if (j > 1)
					System.out.print(" " + cbc[j]);
				else
					System.out.print(cbc[j]);
			}
			System.out.println();
		}
	}
}


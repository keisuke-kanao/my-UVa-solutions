
// UVa 324 - Factorial Frequencies

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 366;
		BigInteger[] factorials = new BigInteger[nMax + 1]; // factorials[i] is factorial of i
		factorials[0] = factorials[1] = BigInteger.ONE;
		for (int i = 2; i <= nMax; i++)
			factorials[i] = factorials[i - 1].multiply(BigInteger.valueOf(i));
/*
		System.out.println(factorials[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int i = sc.nextInt();
			if (i == 0)
				break;
			BigInteger n = factorials[i];
			int[] frequencies = new int[10];
			for ( ; !n.equals(BigInteger.ZERO); n = n.divide(BigInteger.TEN))
				frequencies[n.mod(BigInteger.TEN).intValue()]++;
			System.out.printf("%d! --\n", i);
			for (int j = 0; j < 10; j++) {
				System.out.printf("   (%d)  %3d%c", j, frequencies[j], ((j == 4 || j == 9) ? '\n' : ' '));
			}
		}
	}
}


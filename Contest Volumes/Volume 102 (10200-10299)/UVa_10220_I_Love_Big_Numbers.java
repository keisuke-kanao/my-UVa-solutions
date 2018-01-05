
// UVa 10220 - I Love Big Numbers !

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 1000;
		BigInteger[] factorials = new BigInteger[nMax + 1]; // factorials[i] is factorial of i
		factorials[0] = factorials[1] = BigInteger.ONE;
		for (int i = 2; i <= nMax; i++)
			factorials[i] = factorials[i - 1].multiply(BigInteger.valueOf(i));
/*
		System.out.println(factorials[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			BigInteger i = factorials[n];
			int sumOfDigits = 0;
			for ( ; !i.equals(BigInteger.ZERO); i = i.divide(BigInteger.TEN))
				sumOfDigits += i.mod(BigInteger.TEN).intValue();
			System.out.println(sumOfDigits);
		}
	}
}


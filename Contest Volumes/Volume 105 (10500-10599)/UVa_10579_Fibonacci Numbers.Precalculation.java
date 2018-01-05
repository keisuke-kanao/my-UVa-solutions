
// UVa 10579 - Fibonacci Numbers

import java.util.Scanner;
import java.util.ArrayList;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int maxNumberOfDigits = 1000;
		ArrayList<BigInteger> fibonacciNumbers = new ArrayList<BigInteger>();
		fibonacciNumbers.add(BigInteger.ZERO);
		fibonacciNumbers.add(BigInteger.ONE);
		BigInteger ppfb = BigInteger.ZERO, pfb = BigInteger.ONE;
		for (int i = 2; ; i++) {
			BigInteger fb = pfb.add(ppfb);
			int numberOfDigits = 0;
			for (BigInteger j = fb; !j.equals(BigInteger.ZERO); j = j.divide(BigInteger.TEN))
				if (++numberOfDigits > maxNumberOfDigits)
					break;
			if (numberOfDigits > maxNumberOfDigits)
				break;
			fibonacciNumbers.add(fb);
			ppfb = pfb; pfb = fb;
		}
/*
		System.out.println(fibonacciNumbers.size());
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			System.out.println(fibonacciNumbers.get(n));
		}
	}
}



// UVa 10579 - Fibonacci Numbers

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 4787;
		BigInteger[] fibonacciNumbers = new BigInteger[nMax + 1];
		fibonacciNumbers[0] = BigInteger.ZERO;
		fibonacciNumbers[1] = BigInteger.ONE;
		for (int i = 2; i <= nMax; i++)
			fibonacciNumbers[i] = fibonacciNumbers[i - 1].add(fibonacciNumbers[i - 2]);
/*
		System.out.println(fibonacciNumbers.length);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			System.out.println(fibonacciNumbers[n]);
		}
	}
}


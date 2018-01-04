
// UVa 495 - Fibonacci Freeze

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int maxNumberOfFibonacciNumbers = 5001;
		BigInteger[] FibonacciNumbers = new BigInteger[maxNumberOfFibonacciNumbers];
		FibonacciNumbers[0] = BigInteger.ZERO;
		FibonacciNumbers[1] = BigInteger.ONE;
		for (int i = 2; i < maxNumberOfFibonacciNumbers; i++)
			FibonacciNumbers[i] = FibonacciNumbers[i - 1].add(FibonacciNumbers[i - 2]);
/*
		System.out.println(FibonacciNumbers[maxNumberOfFibonacciNumbers - 1]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			System.out.println("The Fibonacci number for " + n + " is " + FibonacciNumbers[n]);
		}
	}
}


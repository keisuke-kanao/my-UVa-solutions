
// UVa 10334 - Ray Through Glasses

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 1000;
		BigInteger[] fibonacciNumbers = new BigInteger[nMax + 1];
		fibonacciNumbers[0] = BigInteger.ONE;
		fibonacciNumbers[1] = BigInteger.valueOf(2);
		for (int i = 2; i <= nMax; i++)
			fibonacciNumbers[i] = fibonacciNumbers[i - 1].add(fibonacciNumbers[i - 2]);
/*
		System.out.println(fibonacciNumbers[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt())
			System.out.println(fibonacciNumbers[sc.nextInt()]);
	}
}


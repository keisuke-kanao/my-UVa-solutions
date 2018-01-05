
// UVa 10925 - Krakovia

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for (int bill = 1; ; bill++) {
			int n = sc.nextInt(), f = sc.nextInt();
			if (n == 0 && f == 0)
				break;
			BigInteger sum = BigInteger.ZERO;
			for (int i = 0; i < n; i++)
				sum = sum.add(sc.nextBigInteger());
			BigInteger pay = sum.divide(BigInteger.valueOf(f));
			System.out.println("Bill #" + bill + " costs " + sum + ": each friend should pay " + pay);
			System.out.println();
		}
	}
}


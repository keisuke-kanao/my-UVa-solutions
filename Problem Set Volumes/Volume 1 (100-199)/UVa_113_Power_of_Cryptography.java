
// Uva 113 - Power of Cryptography
// Another accepted solution.

/*
	For k^n = p, getting the logarithm of both sides results in:
		n * log(k) = log(p).
		k = exp(log(p) / n).
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			int n = sc.nextInt();
			BigInteger p = sc.nextBigInteger();
			int k = (int)(Math.exp(Math.log(p.doubleValue()) / n));
			while (p.compareTo(BigInteger.valueOf(k).pow(n)) > 0)
				k++;
			System.out.println(k);
		}
	}
}


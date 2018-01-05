
// UVa 10433 - Automorphic Numbers

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			String s = sc.next();
			BigInteger n = new BigInteger(s);
			String t = n.multiply(n).toString();
			if (!n.equals(BigInteger.ZERO) && !n.equals(BigInteger.ONE) && t.endsWith(s))
				System.out.printf("Automorphic number of %d-digit.\n", s.length());
			else
				System.out.println("Not an Automorphic number.");
		}
	}
}


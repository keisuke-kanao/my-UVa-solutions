
// UVa 374 - Big Mod

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			BigInteger b = sc.nextBigInteger(), p = sc.nextBigInteger(), m = sc.nextBigInteger();
			System.out.println(b.modPow(p, m));
		}
	}
}


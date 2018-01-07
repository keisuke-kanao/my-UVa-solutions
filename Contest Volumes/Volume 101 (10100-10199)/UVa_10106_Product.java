
// UVa 10106 - Product

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			BigInteger i = sc.nextBigInteger(), j = sc.nextBigInteger();
			System.out.println(i.multiply(j));
		}
	}
}


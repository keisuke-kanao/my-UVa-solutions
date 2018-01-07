
// UVa 10494 - If We Were a Child Again

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			BigInteger oneNumber = sc.nextBigInteger();
			String op = sc.next();
			BigInteger anotherNumber = sc.nextBigInteger();
			if (op.equals("/"))
				System.out.println(oneNumber.divide(anotherNumber));
			else
				System.out.println(oneNumber.mod(anotherNumber));
		}
	}
}


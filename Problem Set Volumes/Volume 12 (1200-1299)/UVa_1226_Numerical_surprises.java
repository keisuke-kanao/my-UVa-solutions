
// 	UVa 1226 - Numerical surprises

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int ds = sc.nextInt();
		while (ds-- > 0) {
			BigInteger N = sc.nextBigInteger(), P = sc.nextBigInteger();
			System.out.println(P.mod(N));
		}
	}
}


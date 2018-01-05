
//  UVa 10430 - Dear GOD

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		System.out.println("Dear GOD, Pardon Me");
	    Scanner sc = new Scanner(System.in);
		boolean printed = false;
		while (sc.hasNextInt()) {
			if (printed)
				System.out.println();
			else
				printed = true;
			int t = sc.nextInt();
			if (t == 1) {
				int n = sc.nextInt();
				System.out.println("X = " + n);
				System.out.println("K = " + 1);
			}
			else {
				BigInteger T = BigInteger.valueOf(t);
				int n = sc.nextInt();
				BigInteger Tp = T.pow(n); // T^n
				BigInteger Ts = Tp.subtract(BigInteger.ONE).divide(T.subtract(BigInteger.ONE)); // (T^n - 1) / (T - 1)
				// X * T^n = K * (T^n - 1) / (T - 1)
				BigInteger gcd = Tp.gcd(Ts);
				System.out.println("X = " + Ts.divide(gcd));
				System.out.println("K = " + Tp.divide(gcd));
			}
		}
	}
}



// UVa 10523 - Very Easy !!!

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			BigInteger a = sc.nextBigInteger();
			BigInteger series = BigInteger.ZERO, p = BigInteger.ONE;
			for (int i = 1; i <= n; i++) {
				p = p.multiply(a);
				series = series.add(p.multiply(BigInteger.valueOf(i)));
			}
			System.out.println(series);
		}
	}
}


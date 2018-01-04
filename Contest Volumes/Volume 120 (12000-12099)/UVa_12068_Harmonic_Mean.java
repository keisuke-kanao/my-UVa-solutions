
// 12068 - Harmonic Mean
// This solution has not been submitted yet.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int S = sc.nextInt();
		for (int s = 1; s <= S; s++) {
			int N = sc.nextInt();
			BigInteger[] numbers = new BigInteger[N];
			for (int i = 0; i < N; i++)
				numbers[i] = sc.nextBigInteger();
			BigInteger numerator = BigInteger.valueOf(N), denominator = BigInteger.ZERO;
			for (int i = 0; i < N; i++) {
				numerator = numerator.multiply(numbers[i]);
				BigInteger b = BigInteger.ONE;
				for (int j = 0; j < N - 1; j++) {
					b = b.multiply(numbers[(i + j) % N]);
				}
				denominator = denominator.add(b);
			}
			BigInteger g = numerator.gcd(denominator);
			System.out.println("Case " + s + ": " + numerator.divide(g) + "/" + denominator.divide(g));
		}
	}
}


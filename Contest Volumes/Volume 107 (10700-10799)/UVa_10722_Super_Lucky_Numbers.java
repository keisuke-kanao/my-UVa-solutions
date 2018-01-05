
// UVa 10722 - Super Lucky Numbers
// This is an accepted solution.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
//		long start = System.currentTimeMillis();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int B = sc.nextInt(), N = sc.nextInt();
			if (B == 0)
				break;
			BigInteger bOne = BigInteger.valueOf(B - 1), bOthers = BigInteger.valueOf(B - 2);
			BigInteger tailOne = BigInteger.ONE, tailOthers = bOthers;
			for (int i = 2 ; i <= N ; i++) {
				BigInteger tOne = tailOne.add(tailOthers);
					// tailOne = tailOne + tailOthers
				BigInteger tOthers = tailOne.multiply(bOthers).add(tailOthers.multiply(bOne));
					// tailOthers = tailOne * (B - 2) + tailOthers * (B - 1)
				tailOne = tOne;
				tailOthers = tOthers;
			}
			System.out.println(tailOne.add(tailOthers));
		}
//		System.err.printf("%d milliseconds elapsed.\n", System.currentTimeMillis() - start);
	}
}


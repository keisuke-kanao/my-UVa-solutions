
// 	UVa 10359 - Tiling

// This problem is similar to 	UVa 900 - Brick Wall Patterns.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 250;
		final BigInteger TWO = BigInteger.valueOf(2);
		BigInteger[] tilings = new BigInteger[nMax + 1];
		tilings[0] = tilings[1] = BigInteger.ONE;
		// tilings[i] = tilings[i - 1] + 2 * tilings[i - 2]
		for (int i = 2; i <= nMax; i++)
			tilings[i] = tilings[i - 2].multiply(TWO).add(tilings[i - 1]);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt())
			System.out.println(tilings[sc.nextInt()]);
	}
}


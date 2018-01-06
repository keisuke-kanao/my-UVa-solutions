
// UVa 10007 - Count the Trees

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 300;
		final BigInteger TWO = BigInteger.valueOf(2);
		BigInteger[] numberOfTrees = new BigInteger[nMax + 1];
			// numberOfTrees[i] = (i!) * C(i), where C(i) is the i-th Catalan number
		numberOfTrees[0] = numberOfTrees[1] = BigInteger.ONE;
		for (int i = 2; i <= nMax; i++)
			numberOfTrees[i] = TWO.multiply(BigInteger.valueOf(2 * i - 1)).
				multiply(numberOfTrees[i - 1]).divide(BigInteger.valueOf(i + 1)).multiply(BigInteger.valueOf(i));
/*
		System.out.println(numberOfTrees[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			if (n == 0)
				break;
			System.out.println(numberOfTrees[n]);
		}
	}
}


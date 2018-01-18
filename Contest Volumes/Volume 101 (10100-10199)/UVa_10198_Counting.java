
/*
	6.6.3 Counting
	PC/UVa IDs: 110603/10198, Popularity: B, Success rate: high Level: 2
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	private static final int maxNumber = 1000;
	private static final BigInteger BI2 = BigInteger.valueOf(2);

	public static void main(String[] args) {
		BigInteger[] countings = new BigInteger[maxNumber];
		countings[0] = BI2;
		countings[1] = BigInteger.valueOf(5);
		countings[2] = BigInteger.valueOf(13);
		for (int i = 3; i < maxNumber; i++)
			countings[i] = countings[i - 1].multiply(BI2).add(countings[i - 2]).add(countings[i - 3]);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt())
			System.out.println(countings[sc.nextInt() - 1]);
	}
}


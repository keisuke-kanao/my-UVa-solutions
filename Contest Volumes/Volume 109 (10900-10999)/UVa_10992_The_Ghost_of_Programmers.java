
// 	UVa 10992 - The Ghost of Programmers

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final String[] ghosts = {
			"Tanveer Ahsan", "Shahriar Manzoor", "Adrian Kugel", "Anton Maydell",
			"Derek Kisman", "Rezaul Alam Chowdhury", "Jimmy Mardell", "Monirul Hasan",
			"K. M. Iftekhar"
		};
		final BigInteger firstYear = BigInteger.valueOf(2148);
		final BigInteger[] divisors = {
			BigInteger.valueOf(2), BigInteger.valueOf(5), BigInteger.valueOf(7), BigInteger.valueOf(11),
			BigInteger.valueOf(15), BigInteger.valueOf(20), BigInteger.valueOf(28), BigInteger.valueOf(36)
		};

		Scanner sc = new Scanner(System.in);
		boolean printed = false;
		while (true) {
			BigInteger Y = sc.nextBigInteger();
			if (Y.compareTo(BigInteger.ZERO) == 0)
				break;
			if (printed)
				System.out.println();
			else
				printed = true;
			System.out.println(Y);
			BigInteger year = Y.subtract(firstYear);
			if (year.compareTo(BigInteger.ZERO) >= 0) {
				boolean comes = false;
				for (int i = 0; i < 8; i++)
					if (year.remainder(divisors[i]).compareTo(BigInteger.ZERO) == 0) {
						comes = true;
						System.out.println("Ghost of " + ghosts[i] + "!!!");
					}
				if (isLeapYear(Y)) {
					comes = true;
					System.out.println("Ghost of " + ghosts[8] + "!!!");
				}
				if (!comes)
					System.out.println("No ghost will come in this year");
			}
			else
				System.out.println("No ghost will come in this year");
		}
	}

	static boolean isLeapYear(BigInteger year) {
		final BigInteger FOUR = BigInteger.valueOf(4), HUNDRED = BigInteger.valueOf(100), FOUR_HUNDRED = BigInteger.valueOf(400);
		if (year.remainder(FOUR).compareTo(BigInteger.ZERO) != 0)
			return false;
		else if (year.remainder(HUNDRED).compareTo(BigInteger.ZERO) != 0)
			return true;
		else if (year.remainder(FOUR_HUNDRED).compareTo(BigInteger.ZERO) != 0)
			return false;
		else
			return true;
	}
}

/*
Sample Input

2500
3000
0

Output for Sample Input

2500
Ghost of Tanveer Ahsan!!!
Ghost of Anton Maydell!!!

3000
Ghost of Tanveer Ahsan!!!

*/


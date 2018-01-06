
/*
	UVa 10083 - Division

	from 17 January 2001 - Waterloo local contest, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/010127/data/)
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			final int nrDigitsMax = 100;
			final String str = "is not an integer with less than 100 digits.";
			int t = sc.nextInt(), a = sc.nextInt(), b = sc.nextInt();
				System.out.printf("(%d^%d-1)/(%d^%d-1) ", t, a, t, b);
			// (t^a - 1) / (t^b - 1) = 1 + sum of {t^(b * i) (i = 1, 2, ..., a / b - 1)}, if a % b == 0
			if (t == 1)
				System.out.println(str);
			else if (a % b == 0) {
				double logt = Math.log10(t);
				BigInteger bt = BigInteger.valueOf(t), s = BigInteger.ONE;
				int i;
				for (i = a / b - 1; i > 0; i--) {
					int nrDigits = (int)((double)(b * i) * logt + 1.0); // calculate the number of digits of t^(b * i)
					if (nrDigits > nrDigitsMax)
						break;
						s = s.add(bt.pow(b * i));
				}
				if (i > 0)
					System.out.println(str);
				else {
					String ss = s.toString();
					if (ss.length() > nrDigitsMax)
						System.out.println(str);
					else
						System.out.println(ss);
				}
			}
			else
				System.out.println(str);
		}
	}
}


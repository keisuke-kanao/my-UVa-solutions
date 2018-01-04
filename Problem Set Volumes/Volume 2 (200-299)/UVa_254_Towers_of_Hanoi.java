
// UVa 254 - Towers of Hanoi

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final BigInteger TWO = BigInteger.valueOf(2);

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			int n = sc.nextInt();
			BigInteger m = sc.nextBigInteger();
			if (n == 0 && m.equals(BigInteger.ZERO))
				break;
/*
	T.R. Walsh:
	p[m] - peg on which the m-th disk is placed
	b - tests bits of k
	jm1, jm - values of 2 consecutive bits of k
*/
			int[] p = new int[n + 4];
			p[n + 1]= 1;  // base of peg 1, etc.
			p[n + 2]= 2;
			p[n + 3]= 3;
			BigInteger b = TWO.pow(n - 1), jm = m.and(b);
			p[n] = (jm.equals(BigInteger.ZERO)) ? 1 : 3;
			for (int pi = n - 1; pi > 0; pi--) {
				BigInteger jm1 = jm.shiftRight(1);
				b = b.shiftRight(1);
				jm = m.and(b);
				if (jm.equals(jm1))
					p[pi] = p[pi + 1];
				else {
					int i;
					for (i = pi + 2; i < n + 4; i++)
						if (p[i] != p[pi + 1])
							break;
					// disk i is on top of one of the other 2 pegs
					if (((i + pi) & 1) != 0) // i, pi have opposite parity
						p[pi] = p[i];
					else
						p[pi] = 6 - p[i] - p[pi + 1];
				}
			}
			int np1 = 0, np2 = 0, np3 = 0;
			for (int pi = n; pi > 0; pi--)
				switch (p[pi]) {
				case 1:
					np1++; break;
				case 2:
					np2++; break;
				default:
					np3++; break;
				}
			if ((n & 1) != 0) // n is odd
				System.out.println(np1 + " " + np3 + " " + np2);
			else
				System.out.println(np1 + " " + np2 + " " + np3);
		}
	}
}


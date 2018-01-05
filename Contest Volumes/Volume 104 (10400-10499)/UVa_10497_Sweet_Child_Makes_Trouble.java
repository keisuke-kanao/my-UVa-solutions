
// UVa 10497 - Sweet Child Makes Trouble

/*
In combinatorial mathematics, a derangement is a permutation of the elements of a set such that 
none of the elements appear in their original position.
The number of derangements of a set of size n, usually written Dn, dn, or !n, 
is called the "derangement number" or "de Montmort number".

!n = (n - 1) * (!(n - 1) + !(n - 2)
where !n, known as the subfactorial, represents the number of derangements, 
with the starting values !0 = 1 and !1 = 0.
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 800;
		BigInteger[] derangementNrs = new BigInteger[nMax + 1]; // derangementNrs[i] is derangement number of i
		derangementNrs[0] = BigInteger.ONE;
		derangementNrs[1] = BigInteger.ZERO;
		for (int i = 2; i <= nMax; i++)
			derangementNrs[i] = derangementNrs[i - 1].add(derangementNrs[i - 2]).multiply(BigInteger.valueOf(i - 1));
/*
		System.out.println(derangementNrs[nMax]);
*/
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			if (n == -1)
				break;
			System.out.println(derangementNrs[n]);
		}
	}
}


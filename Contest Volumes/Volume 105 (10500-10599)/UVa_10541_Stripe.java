
// UVa 10541 - Stripe
// This is an accepted solution.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	static final int nMax = 200, kMax = 100;
	static int nrs[] = new int[kMax + 1];
	static BigInteger nrRectangles[][] = new BigInteger[kMax + 1][nMax + 1];
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		while (T-- > 0) {
			int N = sc.nextInt(), K = sc.nextInt();
			for (int i = 1; i <= K; i++)
				nrs[i] = sc.nextInt();
			for (int n = 0; n <= N; n++)
				nrRectangles[0][n] = BigInteger.ONE;
			for (int k = 1; k <= K; k++)
				for (int n = 0; n <= N; n++)
					nrRectangles[k][n] = BigInteger.ZERO;
			for (int k = 1, s = 0; k <= K; k++) {
				for (int n = s + nrs[k]; n <= N; n++) {
					if (k > 1)
						nrRectangles[k][n] = nrRectangles[k][n - 1].add(nrRectangles[k - 1][n - nrs[k] - 1]);
					else
						nrRectangles[k][n] = nrRectangles[k][n - 1].add(nrRectangles[k - 1][n - nrs[k]]);
				}
				s += nrs[k] + 1;
			}
			System.out.println(nrRectangles[K][N]);
		}
	}
}


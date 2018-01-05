
// UVa_10328_Coin_Toss.java

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		final int nMax = 100, kMax = 100;
		BigInteger[][][] nrSeqs = new BigInteger[nMax + 1][nMax + 1][kMax + 1];
		for (int i = 0; i <= nMax; i++)
			for (int j = 0;j <= nMax; j++)
				for (int k = 0;k <= kMax; k++)
					nrSeqs[i][j][k] = BigInteger.ZERO;
		nrSeqs[0][0][0] = BigInteger.ONE;
		for (int i = 0; i < nMax; i++)
			for (int j = 0;j <= i; j++) // max number of consecutive heads in i coins
				for (int k = 0; k <= j; k++) // number of cosecutive heads from the last coin
					if (nrSeqs[i][j][k].compareTo(BigInteger.ZERO) != 0) {
						nrSeqs[i + 1][Math.max(j, k + 1)][k + 1] = nrSeqs[i + 1][Math.max(j, k + 1)][k + 1].add(nrSeqs[i][j][k]);
						nrSeqs[i + 1][j][0] = nrSeqs[i + 1][j][0].add(nrSeqs[i][j][k]);
					}
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int n = sc.nextInt(), k = sc.nextInt();
			BigInteger s = BigInteger.ZERO;
			for (int i = k; i <= n; i++)
				for (int j = 0; j <= n; j++)
					s = s.add(nrSeqs[n][i][j]);
				System.out.println(s);
		}
	}
}


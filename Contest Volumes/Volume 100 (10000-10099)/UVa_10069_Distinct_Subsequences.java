
/*
	11.6.2 Distinct Subsequences
	PC/UVa IDs: 111102/10069, Popularity: B, Success rate: average Level: 3
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		try {
			int n = sc.nextInt(); // number of test cases
			while (n-- != 0) {
				String t = ' ' + sc.next(), s = ' ' + sc.next();
				System.out.println(countDistinctSubsequences(s, t));
			}
		}
		catch (RuntimeException e) { // NoSuchElementException (or IllegalStateException)
		}
	}

	static BigInteger countDistinctSubsequences(String s, String t) {
		BigInteger[][] ds = new BigInteger[2][t.length()];
		ds[0][0] = BigInteger.ONE;
		for (int j = 1; j < t.length(); j++)
			ds[0][j] = BigInteger.ZERO;
		for (int i = 1; i < s.length(); i++) {
			int pi = (i - 1) % 2, ci = i % 2;
			BigInteger sum = BigInteger.ZERO;
			for (int j = 0; j < t.length(); j++)
				ds[ci][j] = BigInteger.ZERO;
			for (int j = i; j < t.length(); j++) {
				sum = sum.add(ds[pi][j - 1]);
				if (s.charAt(i) == t.charAt(j))
					ds[ci][j] = sum;
			}
		}
		BigInteger count = BigInteger.ZERO;
		for (int i = (s.length() - 1) % 2, j = 1; j < t.length(); j++)
			count = count.add(ds[i][j]);
		return count;
	}
}


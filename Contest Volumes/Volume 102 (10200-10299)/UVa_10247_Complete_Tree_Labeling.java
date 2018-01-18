
/*
	6.6.5 Complete Tree Labeling
	PC/UVa IDs: 110605/10247, Popularity: C, Success rate: average Level: 2
*/

/*
total number of nodes for a k-ary tree of depth d = Σ(i = 0 to d) pow(k, i) = (pow(k, d + 1) - 1) / (k - 1).
number of nodes at the i-th level of depth = pow(k, i), each of which has pow(k, i + 1) nodes.
*/

import java.util.Scanner;
import java.util.HashMap;
import java.math.BigInteger;

class Main {
	static int numberOfNodes(int k, int d) { // number of nodes for a k-ary tree of depth d
		return ((int)Math.pow((double)k, (double)d + 1.0) - 1) / (k - 1);
	}

	static BigInteger factorial(int n) {
		BigInteger f = BigInteger.ONE;
		for (int i = 1; i <= n; i++)
			f = f.multiply(BigInteger.valueOf(i));
		return f;
	}

	static HashMap<Long, BigInteger> combinationCache = new HashMap<Long, BigInteger>();

	static BigInteger combination(int n, int k) {
		if (k == 0 || n == k)
			return BigInteger.ONE;
		else {
			long nk = (long)n << 32 | k;
			BigInteger c = combinationCache.get(nk);
			if (c != null)
				return c;
			c = factorial(n).divide(factorial(n - k).multiply(factorial(k)));
			combinationCache.put(nk, c);
			return c;
		}
	}

	static HashMap<Long, BigInteger> cache = new HashMap<Long, BigInteger>();

	static BigInteger completeTreeLabeling(int k /* branching factor */, int d /* depth */) {
		if (k == 1)
			return BigInteger.ONE;
		long kd = (long)k << 32 | d;
		BigInteger nrLabeling = cache.get(kd);
		if (nrLabeling != null)
			return nrLabeling;
		nrLabeling = factorial(k);
		if (d > 1) {
			// number of nodes for a k-ary tree of depth d
			int nrNodes = numberOfNodes(k, d);
			// number of descendants of the root node for a k-ary tree of depth (d - 1)
			int nrDescendants = numberOfNodes(k, d - 1) - 1;
			// number of labeling for a k-ary tree of depth (d - 1)
			BigInteger nrDescendantsLabeling = completeTreeLabeling(k, d - 1);
			for (int i = nrNodes - 2; i >= nrDescendants; i -= nrDescendants + 1) {
				BigInteger c = combination(i, nrDescendants);
				nrLabeling = nrLabeling.multiply(c).multiply(nrDescendantsLabeling);
			}
		}
		cache.put(kd, nrLabeling);
		return nrLabeling;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			int k = sc.nextInt();
			if (sc.hasNextInt()) {
				int d = sc.nextInt();
				System.out.println(completeTreeLabeling(k, d));
			}
		}
	}
}


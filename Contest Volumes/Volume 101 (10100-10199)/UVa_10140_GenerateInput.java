
// test data generation for UVa 10140 - Prime Distance

import java.util.Random;

class Main {
	public static void main(String[] args) {
		Random r = new Random();
		for (int i = 0; i < 1000; i++) {
			int L = r.nextInt() % 1073741824, U = r.nextInt() % 1073741824;
			if (L < 0)
				L = -L;
			if (U < 0)
				U = -U;
			if (L == 0)
				L++;
			if (U == 0)
				U++;
			if (L > U) {
				int t = L; L = U; U = t;
			}
			if (U - L > 1000000)
				U = L + 1000000;
			System.out.println(L + " " + U);
		}
	}
}


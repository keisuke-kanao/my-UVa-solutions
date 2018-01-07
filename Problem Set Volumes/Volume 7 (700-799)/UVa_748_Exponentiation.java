
// UVa 748 - Exponentiation

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			String sr = sc.next();
			int n = sc.nextInt();
			int i = sr.indexOf('.');
			int exponentOf10 = sr.length() - i - 1;
			boolean lessThanOne = sr.charAt(0) == '0' || sr.charAt(0) == '.';
			sr = (lessThanOne) ? sr.substring(i + 1) : sr.substring(0, i) + sr.substring(i + 1);
			BigInteger r = new BigInteger(sr);
			BigInteger rn = r.pow(n);
			StringBuffer srn = new StringBuffer(rn.toString(10));
			int zeros = exponentOf10 * n;
			if (lessThanOne) {
				zeros -= srn.length();
				srn.insert(0, '.');
				while (zeros-- > 0)
					srn.insert(1, '0');
			}
			else
				srn.insert(srn.length() - zeros, '.');
			// remove the trailing zeros
			int l = srn.length() - 1;
			for ( ; l >= 0; l--) {
				if (srn.charAt(l) != '0') {
					if (srn.charAt(l) == '.')
						l--;
					break;
				}
			}
			System.out.println(srn.substring(0, l + 1).toString());
		}
	}
}


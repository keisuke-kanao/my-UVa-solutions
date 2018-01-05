
// UVa 10464 - Big Big Real Numbers
// Can be rewritten using java.math.BigDecimal in a simpler manner.

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		while (N-- > 0) {
			RealNumber ri = new RealNumber(sc.next()), rj = new RealNumber(sc.next());
			BigInteger bi = new BigInteger(ri.integerPart + ri.decimalPart), bj = new BigInteger(rj.integerPart + rj.decimalPart);
			int ridl = ri.decimalPart.length(), rjdl = rj.decimalPart.length();
			int nrDecimalDigits = Math.max(ridl, rjdl);
			if (nrDecimalDigits > ridl)
				bi = bi.multiply(BigInteger.TEN.pow(nrDecimalDigits - ridl));
			if (nrDecimalDigits > rjdl)
				bj = bj.multiply(BigInteger.TEN.pow(nrDecimalDigits - rjdl));
			bi = bi.add(bj);
			int sign = bi.signum();
			bi = bi.abs();
			String rs = bi.toString();
			int iDecimalPoint = rs.length() - nrDecimalDigits;
			String integerPart, decimalPart;
			if (iDecimalPoint >= 0) {
				integerPart = rs.substring(0, iDecimalPoint);
				decimalPart = removeTrailingZeros(rs.substring(iDecimalPoint));
			}
			else {
				integerPart = "";
				StringBuilder sb = new StringBuilder();
				for (iDecimalPoint = -iDecimalPoint; iDecimalPoint > 0; iDecimalPoint--)
					sb.append('0');
				decimalPart = removeTrailingZeros(sb.toString() + rs);
			}
			if (sign < 0)
				System.out.print('-');
			System.out.printf("%s.%s\n",
				((integerPart.isEmpty()) ? "0" : integerPart.trim()), ((decimalPart.isEmpty()) ? "0" : decimalPart.trim()));
		}
	}

	static String removeTrailingZeros(final String s) {
		int i = s.length() - 1;
		while (i >= 0 && s.charAt(i) == '0')
			i--;
		return s.substring(0, i + 1);
	}
}

class RealNumber {
	public String integerPart, decimalPart;

	RealNumber(final String s) {
		int iDecimalPoint = s.indexOf('.');
		if (iDecimalPoint != -1) {
			integerPart = s.substring(0, iDecimalPoint);
			decimalPart = s.substring(iDecimalPoint + 1);
		}
		else {
			integerPart = s; decimalPart = "";
		}
		if (integerPart.isEmpty())
			integerPart = "0";
		if (decimalPart.isEmpty())
			decimalPart = "0";
	}
}



// 	UVa 11821 - High-Precision Number

import java.util.Scanner;
import java.math.BigDecimal;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		while (n-- > 0) {
			BigDecimal s = BigDecimal.ZERO;
			while (true) {
				String ds = sc.next();
				if (ds.equals("0"))
					break;
				s = s.add(new BigDecimal(ds));
			}
			String ss = s.toString();
			int di = ss.indexOf('.');
			if (di != -1) {
				int i = ss.length() - 1;
				for ( ; i >= di; i--)
					if (ss.charAt(i) != '0')
						break;
				if (ss.charAt(i) == '.')
					i--;
				ss = ss.substring(0, i + 1);
			}
			System.out.println(ss);
		}
	}
}


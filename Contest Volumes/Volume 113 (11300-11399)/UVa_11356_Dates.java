
// UVa 11356 - Dates

import java.util.Scanner;
import java.util.Calendar;

class Main {
	static final String[] months = {
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};

	public static void main(String[] args) {
		Calendar cal = Calendar.getInstance();
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		for (int t = 1; t <= T; t++) {
			String[] s = sc.next().split("-");
			int year = Integer.valueOf(s[0]), month = getMonth(s[1]), day = Integer.valueOf(s[2]);
			int K = sc.nextInt();
			cal.set(year, month, day);
			cal.add(Calendar.DATE, K);
			System.out.printf("Case %d: %d-%s-%02d\n", t, cal.get(cal.YEAR), months[cal.get(cal.MONTH)], cal.get(cal.DATE));
		}
	}

	static int getMonth(String month) {
		int m = 0;
		for ( ; m < months.length; m++)
			if (month.equals(months[m]))
				break;
		return m;
	}
}


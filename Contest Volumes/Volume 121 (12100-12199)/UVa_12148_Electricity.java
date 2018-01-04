
// UVa 12148 - Electricity

import java.util.Scanner;
import java.util.Calendar;

class Main {
	public static void main(String[] args) {
		Calendar pc = Calendar.getInstance(), cc = Calendar.getInstance();
		pc.clear(); cc.clear();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int N = sc.nextInt();
			if (N == 0)
				break;
			int D = sc.nextInt(), M = sc.nextInt(), Y = sc.nextInt(), pC = sc.nextInt(), nr = 0, s = 0;
			pc.set(Y, M - 1, D);
			while (--N > 0) {
				pc.add(Calendar.DAY_OF_MONTH, 1);
				D = sc.nextInt(); M = sc.nextInt(); Y = sc.nextInt();
				int C = sc.nextInt();
				cc.set(Y, M - 1, D);
				if (pc.equals(cc)) {
					nr++;
					s += C - pC;
				}
				pc.set(Y, M - 1, D);
				pC = C;
			}
			System.out.printf("%d %d\n", nr, s);
		}
	}
}

/*
Sample input

5
9 9 1979 440
29 10 1979 458
30 10 1979 470
1 11 1979 480
2 11 1979 483
3
5 5 2000 6780
6 5 2001 7795
7 5 2002 8201
8
28 2 1978 112
1 3 1978 113
28 2 1980 220
1 3 1980 221
5 11 1980 500
14 11 2008 600
15 11 2008 790
16 12 2008 810
0

Output for the sample input
2 15
0 0
2 191

*/



// UVa 11945 - Financial Management

import java.util.Scanner;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		for (int n = 1; n <= N; n++) {
			double s = 0.0;
			for (int i = 0; i < 12; i++)
				s += sc.nextDouble();
			System.out.printf("%d $%,.2f\n", n, s / 12.0);
		}
	}
}


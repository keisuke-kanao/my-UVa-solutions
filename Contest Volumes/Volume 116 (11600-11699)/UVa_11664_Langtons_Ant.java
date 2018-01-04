
// 	UVa 11664 - Langton's Ant

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			int n = sc.nextInt();
			if (n == 0)
				break;
			boolean world[][] = new boolean[n][n];
			BigInteger c = sc.nextBigInteger();
			for (int i = n * n - 1, j = 0; i >= 0; i--, j++)
				world[j / n][j % n] = c.testBit(i);
			int x = sc.nextInt(), y = sc.nextInt();
			x--; y--;
			final int nrDirs = 4, dirs[][] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
			int di = 1;
			boolean reached = false;
			while (true) {
				if (x == n - 1 && y == n - 1) {
					reached = true; break;
				}
				di = (world[y][x]) ? (di + nrDirs - 1) % nrDirs : (di + nrDirs + 1) % nrDirs;
				world[y][x] = !world[y][x];
				y += dirs[di][0]; x += dirs[di][1];
				if (y < 0 || y >= n || x < 0 || x >= n)
					break;
			}
			System.out.println((reached) ? "Yes" : "Kaputt!");
		}
	}
}


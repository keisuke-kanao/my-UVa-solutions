
/*
	UVa 11953 - Battleships

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11953_Battleships.cpp
*/

#include <cstdio>

const int N_max = 100;
char grid[N_max][N_max + 1];

bool battleship(int N, int r, int& c)
{
	bool alive = grid[r][c] == 'x';
	grid[r][c] = '.';
	int rr = r + 1, cc = c + 1;
	if (cc < N && (grid[r][cc] == 'x' || grid[r][cc] == '@')) { // placed horizontally
		do {
			if (grid[r][cc] == 'x')
				alive = true;
			grid[r][cc] = '.';
		} while (++cc < N && (grid[r][cc] == 'x' || grid[r][cc] == '@'));
		c = cc;
	}
	else if (rr < N && (grid[rr][c] == 'x' || grid[rr][c] == '@')) { // placed vertically
		do {
			if (grid[rr][c] == 'x')
				alive = true;
			grid[rr][c] = '.';
		} while (++rr < N && (grid[rr][c] == 'x' || grid[rr][c] == '@'));
	}
	return alive;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		for (int r = 0; r < N; r++)
			scanf("%s", grid[r]);
		int nr_alive = 0;
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; ) {
				if (grid[r][c] == 'x' || grid[r][c] == '@') {
					if (battleship(N, r, c))
						nr_alive++;
				}
				else
					c++;
			}
		printf("Case %d: %d\n", t, nr_alive);
	}
	return 0;
}


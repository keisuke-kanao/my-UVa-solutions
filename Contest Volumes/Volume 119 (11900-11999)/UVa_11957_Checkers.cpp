
/*
	UVa 11957 - Checkers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11957_Checkers.cpp
*/

#include <cstdio>

const int N_max = 100, divisor = 1000007;

char board[N_max][N_max + 1];
int N, nr_paths[N_max][N_max];
	// nr_paths[y][x] is the number of paths to the cell (x, y)

int from_left(int y, int x, bool jumped)
{
	y++, x--;
	if (y < N && x >= 0) {
		if (board[y][x] != 'B')
			return nr_paths[y][x];
		else
			return (jumped) ? 0 : from_left(y, x, true);
	}
	else
		return 0;
}

int from_right(int y, int x, bool jumped)
{
	y++, x++;
	if (y < N && x < N) {
		if (board[y][x] != 'B')
			return nr_paths[y][x];
		else
			return (jumped) ? 0: from_right(y, x, true);
	}
	else
		return 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		int sy, sx;
		for (int y = 0; y < N; y++) {
			scanf("%s", board[y]);
			for (int x = 0; x < N; x++)
				if (board[y][x] == 'W')
					sy = y, sx = x;
		}
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				nr_paths[y][x] = 0;
		nr_paths[sy][sx] = 1;
		for (int y = sy - 1; y >= 0; y--)
			for (int x = 0; x < N; x++)
				if (board[y][x] != 'B')
					nr_paths[y][x] = (from_left(y, x, false) + from_right(y, x, false)) % divisor;
		int nr = 0;
		for (int x  = 0; x < N; x++) {
			nr += nr_paths[0][x];
			nr %= divisor;
		}
		printf("Case %d: %d\n", t, nr);
	}
	return 0;
}


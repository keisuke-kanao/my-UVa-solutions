
/*
	UVa 11459 - Snakes and Ladders

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11459_Snakes_and_Ladders.cpp
*/

#include <cstdio>

const int die_max = 6, nr_squares = 100, nr_players_max = 1000000;

int players[nr_players_max]; // players[i] is the current square # of i-th player
int squares[nr_squares + die_max];
	// squares[i] is the next square to advance for i-th (i > 0) square

int main()
{
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int i, j, k;
		for (i = 1; i < nr_squares; i++)
			squares[i] = i;
		for ( ; i < nr_squares + die_max; i++)
			squares[i] = nr_squares;
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		for (i = 0; i < a; i++)
			players[i] = 1;
		for (i = 0; i < b; i++) {
			scanf("%d %d", &j, &k);
			squares[j] = k;
		}
		bool game_over = false;
		for (i = 0; i < c; i++) {
			scanf("%d", &j);
			if (!game_over) {
				int& p = players[i % a];
				if ((p = squares[p + j]) == nr_squares)
					game_over = true;
			}
		}
		for (i = 0; i < a; i++)
			printf("Position of player %d is %d.\n", i + 1, players[i]);
	}
	return 0;
}


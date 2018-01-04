
/*
	UVa 12498 - Ant's Shopping Mall

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12498_Ants_Shopping_Mall.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int R_max = 50, C_max = 50;

char mall[R_max][C_max + 1];

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int R, C;
		scanf("%d %d", &R, &C);
		for (int r = 0; r < R; r++)
			scanf("%s", mall[r]);
		int min_nr_moves = -1;
		for (int c = 0; c < C; c++) {
			int nr_moves = 0;
			for (int r = 0; r < R; r++) {
				int min_nr_column_moves = 0;
				if (mall[r][c] == '1') {
					min_nr_column_moves = C;
					for (int i = c - 1; i >= 0; i--)
						if (mall[r][i] == '0') {
							min_nr_column_moves = c - i;
							break;
						}
					for (int i = c + 1; i < C; i++)
						if (mall[r][i] == '0') {
							min_nr_column_moves = min(min_nr_column_moves, i - c);
							break;
						}
				}
				if (min_nr_column_moves == C) {
					nr_moves = -1;
					break;
				}
				else
					nr_moves += min_nr_column_moves;
			}
			if (nr_moves != -1) {
				if (min_nr_moves == -1)
					min_nr_moves = nr_moves;
				else
					min_nr_moves = min(min_nr_moves, nr_moves);
			}
		}
		printf("Case %d: %d\n", t, min_nr_moves);
	}
	return 0;
}


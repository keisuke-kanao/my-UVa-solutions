
/*
	UVa 12187 - Brothers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12187_Brothers.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int R_max = 100, C_max = 100;

int countries[2][R_max][C_max];

int main()
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	while (true) {
		int N, R, C, K;
		scanf("%d %d %d %d", &N, &R, &C, &K);
		if (!N)
			break;
		int (*pc)[R_max][C_max] = &countries[0], (*cc)[R_max][C_max] = &countries[1];
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				scanf("%d", &(*pc)[i][j]);
		for (int k = 0; k < K; k++) {
			for (int i = 0; i < R; i++)
				for (int j = 0; j < C; j++)
					(*cc)[i][j] = (*pc)[i][j];
			for (int i = 0; i < R; i++)
				for (int j = 0; j < C; j++)
					for (int d = 0; d < nr_dirs; d++) {
						int r = i + dirs[d][0], c = j + dirs[d][1];
						if (r >= 0 && r < R && c >= 0 && c < C) {
							int h = (*pc)[r][c];
							if (!h)
								h = N;
							if ((*pc)[i][j] + 1 == h)
								(*cc)[r][c] = (*pc)[i][j];
						}
					}
			swap(pc, cc);
		}
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				printf("%d%c", (*pc)[i][j], ((j < C - 1) ? ' ' : '\n'));
	}
	return 0;
}


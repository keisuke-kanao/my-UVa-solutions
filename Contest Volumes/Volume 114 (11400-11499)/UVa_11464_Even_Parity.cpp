
/*
	UVa 11464 - Even Parity

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11464_Even_Parity.cpp
*/

#include <cstdio>

const int N_max = 15;
int N, min_count, cells[N_max][N_max], transformations[N_max][N_max];

void transformation(int c, int count)
{
	if (c == N) {
		for (int i = 0; i < N - 1; i++)
			for (int j = 0; j < N; j++) {
				int p = 0;
				if (i)
					p += transformations[i - 1][j];
				if (j)
					p += transformations[i][j - 1];
				if (j < N - 1)
					p += transformations[i][j + 1];
				transformations[i + 1][j] = (p & 1) ? 1 : 0;
				if (!transformations[i + 1][j] && cells[i + 1][j]) // transformation of 1 to 0
					return;
				else if (transformations[i + 1][j] != cells[i + 1][j]) {
					if (++count >= min_count)
						return;
				}
			}
		min_count = count;
#ifdef DEBUG
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				printf("%d%c", transformations[i][j], ((j < N - 1) ? ' ' : '\n'));
		printf("%d %d\n", count, min_count);
#endif
	}
	else {
		int cc = cells[0][c];
		transformations[0][c] = cc;
		transformation(c + 1, count);
		if (!min_count)
			return;
		if (!cc && count + 1 < min_count) {
			transformations[0][c] = 1;
			transformation(c + 1, count + 1);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &cells[i][j]);
		min_count = N * N + 1;
		transformation(0, 0);
		printf("Case %d: %d\n", t, ((min_count > N * N) ? -1 : min_count));
	}
	return 0;
}



/*
	UVa 10616 - Divisible Group Sums

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10616_Divisible_Group_Sums.cpp
*/

#include <cstdio>

const int N_max = 200, D_max = 20, M_max = 10;
int integers[N_max + 1];
long long nr_ways[N_max + 1][M_max + 1][D_max];
	// nr_ways[i][j][k] is the number of ways where sum of j integers out of i has the modulo value of k
	// 1 <= i <= N, 1 <= j <= M, 0 <= k < D

int main()
{
	for (int s = 1; ; s++) {
		int N, Q;
		scanf("%d %d", &N, &Q);
		if (!N && !Q)
			break;
		for (int i = 1; i <= N; i++)
			scanf("%d", &integers[i]);
		printf("SET %d:\n", s);
		for (int q = 1; q <= Q; q++) {
			int D, M;
			scanf("%d %d", &D, &M);

			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= M; j++)
					for (int k = 0; k < D; k++)
						nr_ways[i][j][k] = 0;
			for (int i = 1; i <= N; i++) {
				for (int k = 0; k < D; k++)
					nr_ways[i][1][k] = nr_ways[i - 1][1][k];
				int r = integers[i] % D;
				if (r < 0)
					r += D;
				nr_ways[i][1][r]++;
				for (int j = 2; j <= N && j <= M; j++)
					for (int k = 0; k < D; k++)
						nr_ways[i][j][(r + k) % D] = nr_ways[i - 1][j][(r + k) % D] + nr_ways[i - 1][j - 1][k];
#ifdef DEBUG
				for (int j = 1; j <= N && j <= M; j++)
					for (int k = 0; k < D; k++)
						printf("[%d][%d][%d]: %lld%c", i, j, k, nr_ways[i][j][k], ((k < D - 1) ? ' ' : '\n'));
#endif
			}
			printf("QUERY %d: %lld\n", q, nr_ways[N][M][0]);
		}
	}
	return 0;
}


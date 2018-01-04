
/*
	UVa 11472 - Beautiful Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11472_Beautiful_Numbers.cpp
*/

#include <cstdio>

const int N_max = 10, M_max = 100, mask_max = 1 << N_max, divisor = 1000000007;
int nrs[M_max + 1][N_max][mask_max]; // [number of digits][lastdigit used][mask of used digits]

int main()
{
	for (int n = 1; n < N_max; n++)
		nrs[1][n][1 << n] = 1;
	for (int m = 2; m <= M_max; m++) {
		for (int i = 1; i < mask_max; i++)
			nrs[m][1][i | 1] = nrs[m - 1][0][i];
		for (int n = 1; n < N_max - 1; n++)
			for (int i = 1; i < mask_max; i++) {
				nrs[m][n - 1][i | 1 << (n - 1)] += nrs[m - 1][n][i];
				nrs[m][n - 1][i | 1 << (n - 1)] %= divisor;
				nrs[m][n + 1][i | 1 << (n + 1)] += nrs[m - 1][n][i];
				nrs[m][n + 1][i | 1 << (n + 1)] %= divisor;
			}
		for (int i = 1; i < mask_max; i++) {
			nrs[m][N_max - 2][i | 1 << (N_max - 2)] += nrs[m - 1][N_max - 1][i];
			nrs[m][N_max - 2][i | 1 << (N_max - 2)] %= divisor;
		}
	}

	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M;
		scanf("%d %d", &N, &M);
		int mask = 1 << N, nr = 0;
		for (int m = 2; m <= M; m++)
			for (int n = 0; n < N; n++) {
				nr += nrs[m][n][mask - 1];
				nr %= divisor;
			}
		printf("%d\n", nr);
	}
	return 0;
}


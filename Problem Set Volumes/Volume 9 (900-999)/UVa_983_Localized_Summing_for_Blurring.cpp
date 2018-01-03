
/*
	UVa 983 - Localized Summing for Blurring

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_983_Localized_Summing_for_Blurring.cpp

	See also UVa 11951 - Area.
*/

#include <cstdio>

const int N_max = 1000;

int sm[N_max][N_max]; // sm[x][y] is the sum of matrix[i][j] for 0 <= i <= x and 0 <= j <= y

int sum(int xt, int yl, int xb, int yr)
{
	if (xt && yl)
		return sm[xb][yr] - sm[xt - 1][yr] - sm[xb][yl - 1] + sm[xt - 1][yl - 1];
	else if (xt)
		return sm[xb][yr] - sm[xt - 1][yr];
	else if (yl)
		return sm[xb][yr] - sm[xb][yl - 1];
	else
		return sm[xb][yr];
}

int main()
{
	bool printed = false;
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 0; i < N; i++)
			for (int j = 0, s = 0; j < N; j++) {
				int k;
				scanf("%d", &k);
				s += k;
				sm[i][j] = s;
				if (i)
					sm[i][j] += sm[i - 1][j];
			}
		long long s = 0;
		for (int xt = 0; xt < N - M + 1; xt++)
			for (int yl = 0; yl < N - M + 1; yl++) {
				int k = sum(xt, yl, xt + M - 1, yl + M - 1);
				printf("%d\n", k);
				s += k;
			}
		printf("%lld\n", s);
	}
	return 0;
}


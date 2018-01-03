
/*
	UVa 911 - Multinomial Coefficients

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_911_Multinomial_Coefficients.cpp
*/

#include <cstdio>

int main()
{
	const int k_max = 100;
	long long bc[k_max + 1][k_max + 1]; // binomial coefficient
	for (int i = 0; i <= k_max; i++)
		bc[i][0] = 1;
	for (int j = 0; j <= k_max; j++)
		bc[j][j] = 1;
	for (int i = 1; i <= k_max; i++)
		for (int j = 1; j < i; j++)
			bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];

	int n;
	while (scanf("%d", &n) != EOF) {
		int k;
		scanf("%d", &k);
		long long mc = 1;
		while (k--) {
			int i;
			scanf("%d", &i);
			mc *= bc[n][i];
			n -= i;
		}
		printf("%lld\n", mc);
	}
	return 0;
}


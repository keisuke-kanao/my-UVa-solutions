
/*
	UVa 10943 - How do you add?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10943_How_do_you_add.cpp
*/

#include <cstdio>

const int n_max = 100, k_max = 100;
int nr_ways[n_max + 1][k_max + 1];

int main()
{
	int n, k;
	for (k = 1; k <= k_max; k++)
		nr_ways[0][k] = 1;
	for (n = 0; n <= n_max; n++)
		nr_ways[n][1] = 1;
	for (k = 2; k <= k_max; k++)
		for (n = 1; n <= n_max; n++)
			for (int i = 0; i <= n; i++) {
				nr_ways[n][k] += nr_ways[i][k - 1];
				nr_ways[n][k] %= 1000000;
			}
	while (true) {
		scanf("%d %d", &n, &k);
		if (!n && !k)
			break;
		printf("%d\n", nr_ways[n][k]);
	}
	return 0;
}


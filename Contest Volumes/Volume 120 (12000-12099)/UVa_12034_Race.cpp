
/*
	UVa 12034 - Race

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12034_Race.cpp
*/

#include <cstdio>

const int n_max = 1000, modulo = 10056;
int combinations[n_max + 1][n_max + 1];
int nr_ways[n_max + 1]; // nr_ways[i] is the number of way the race can finish with i horses

int main()
{
	// calculate the combinations
	for (int i = 0; i <= n_max; i++)
		combinations[i][0] = 1;
	for (int i = 0; i <= n_max; i++)
		combinations[i][i] = 1;
	for (int i = 1; i <= n_max; i++)
		for (int j = 1; j < i; j++)
			combinations[i][j] = (combinations[i - 1][j - 1] + combinations[i - 1][j]) % modulo;
	nr_ways[1] = 1;
	for (int i = 2; i <= n_max; i++) {
		int nr = 1;
		for (int j = 1; j < i; j++) {
			nr += combinations[i][j] * nr_ways[i - j] % modulo;
			nr %= modulo;
		}
		nr_ways[i] = nr;
	}
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		printf("Case %d: %d\n", t, nr_ways[n]);
	}
	return 0;
}


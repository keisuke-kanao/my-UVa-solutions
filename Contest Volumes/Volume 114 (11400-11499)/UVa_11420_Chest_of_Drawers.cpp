
/*
	UVa 11420 - Chest of Drawers

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_11420_Chest_of_Drawers.cpp
*/

#include <cstdio>

/*
DP: int64 d[maxn][2][maxs]; 
d[n][0/1][s] keep track of the number of ways one can arrange the chest with n drawers with s secured ones, ending with a locked/unlocked chest. 
Complexity: O(n*s) + Q
*/

const int n_max = 65, s_max = 65;
long long nr_ways[n_max + 1][2][s_max + 1];
	// nr_ways[n][0/1][s] is the number of ways for n drawers and with s secured ones, ending with a unlocked(0) / locked (1) chest

int main()
{
	nr_ways[1][0][0] = nr_ways[1][1][1] = 1;
	for (int n = 2; n <= n_max; n++)
		for (int s = 0; s <= n; s++) {
			nr_ways[n][0][s] = nr_ways[n - 1][0][s] + nr_ways[n - 1][1][s];
			nr_ways[n][1][s] = nr_ways[n - 1][0][s];
			if (s)
			 nr_ways[n][1][s] += nr_ways[n - 1][1][s - 1];
#ifdef DEBUG
			printf("[%d][%d]:%lld%c", n, s, nr_ways[n][0][s] + nr_ways[n][1][s], ((s < n) ? ' ' : '\n'));
#endif
		}

	while (true) {
		int n, s;
		scanf("%d %d", &n, &s);
		if (n < 0)
			break;
		printf("%lld\n", nr_ways[n][0][s] + nr_ways[n][1][s]);
	}
	return 0;
}


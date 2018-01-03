
/*
	UVa 907 - Winterim Backpacking Trip

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_907_Winterim_Backpacking_Trip.cpp

	An accepted solution.
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int n_max = 601, k_max = 301;
int values[n_max + 1], prefix_sums[n_max + 1];
int min_partitions[n_max + 1][k_max + 1];

void partition(int n, int k)
{
	for (int i = 1; i <= n; i++)
		min_partitions[i][1] = prefix_sums[i];
	for (int j = 1; j <= k; j++)
		min_partitions[1][j] = values[1];
	for (int i = 2; i <= n; i++)
		for (int j = 2; j <= k; j++) {
			min_partitions[i][j] = numeric_limits<int>::max();
			for (int x = 1; x <= i - 1; x++) {
				int cost = max(min_partitions[x][j - 1], prefix_sums[i] - prefix_sums[x]);
				if (min_partitions[i][j] > cost)
					min_partitions[i][j] = cost;
			}
		}
}

int main()
{
	int n, k;
	while (scanf("%d %d", &n, &k) != EOF) {
		n++; k++;
		for (int i = 1, s = 0; i <= n; i++) {
			scanf("%d", &values[i]);
			s += values[i];
			prefix_sums[i] = s;
		}
		partition(n, k);
		printf("%d\n", min_partitions[n][k]);
	}
	return 0;
}


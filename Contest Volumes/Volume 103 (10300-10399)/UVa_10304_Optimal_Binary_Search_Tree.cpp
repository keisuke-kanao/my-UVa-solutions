
/*
	UVa 10304 - Optimal Binary Search Tree

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10304_Optimal_Binary_Search_Tree.cpp

	Optimal Binary Search Tree is a typical problem that can be solved using Dynamic Programming.
*/

#include <limits>
#include <cstdio>
using namespace std;

const int n_max = 250;
int costs[n_max][n_max]; // costs[i][j] is the sum of costs from i to j
int frequencies[n_max];
int sum_of_frequencies[n_max]; // frequency_sums[i] is the sum of frequencies up to i

// A utility function to get sum of array elements freq[i] to freq[j]
int calculate_sum_of_frequencies(int i, int j)
{
	int s = sum_of_frequencies[j];
	if (i)
		s -= sum_of_frequencies[i - 1];
	return s;
}

int optimal_binary_search_tree(int n)
{
	for (int i = 0; i < n; i++)
		costs[i][i] = frequencies[i];

	for (int k = 2; k <= n; k++) {
		for (int i = 0; i <= n - k + 1; i++) {
			int j = i + k - 1;
			int s = calculate_sum_of_frequencies(i, j);
			costs[i][j] = numeric_limits<int>::max();
			for (int r = i; r <= j; r++) {
				int c = s;
				if (r > i)
					c += costs[i][r - 1];
				if (r < j)
					c += costs[r + 1][j];
               if (c < costs[i][j])
                  costs[i][j] = c;
            }
        }
    }
    return costs[0][n - 1];
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		int f = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &frequencies[i]);
			f += frequencies[i];
			sum_of_frequencies[i] = f;
		}
		printf("%d\n", optimal_binary_search_tree(n) - calculate_sum_of_frequencies(0, n - 1));
	}
}


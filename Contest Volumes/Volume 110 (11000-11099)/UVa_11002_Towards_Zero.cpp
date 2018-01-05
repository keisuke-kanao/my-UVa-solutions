
/*
	UVa 11002 - Towards Zero

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11002_Towards_Zero.cpp
*/

#include <algorithm>
#include <set>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N_max = 30, n_max = 50;

set<int> results[2 * N_max - 1][N_max];

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j <= i; j++)
				results[i][j].clear();
		for (int i = N; i < 2 * N - 1; i++)
			for (int j = 0; j <= 2 * (N - 1) - i; j++)
				results[i][j].clear();
		int n;
		scanf("%d", &n);
		results[0][0].insert(n);
		for (int i = 1; i < N; i++)
			for (int j = 0; j <= i; j++) {
				scanf("%d", &n);
				for (set<int>::const_iterator k = results[i - 1][j].begin(); k != results[i - 1][j].end(); ++k) {
					results[i][j].insert(*k + n);
					results[i][j].insert(*k - n);
				}
				if (j)
					for (set<int>::const_iterator k = results[i - 1][j - 1].begin(); k != results[i - 1][j - 1].end(); ++k) {
						results[i][j].insert(*k + n);
						results[i][j].insert(*k - n);
					}
#ifdef DEBUG
				printf("[%d][%d]: %u\n", i, j, results[i][j].size());
				for (set<int>::const_iterator k = results[i][j].begin(); k != results[i][j].end(); ++k)
					printf(" %d", *k);
				putchar('\n');
#endif
			}
		for (int i = N; i < 2 * N - 1; i++)
			for (int j = 0; j <= 2 * (N - 1) - i; j++) {
				scanf("%d", &n);
				for (set<int>::const_iterator k = results[i - 1][j].begin(); k != results[i - 1][j].end(); ++k) {
					results[i][j].insert(*k + n);
					results[i][j].insert(*k - n);
				}
				for (set<int>::const_iterator k = results[i - 1][j + 1].begin(); k != results[i - 1][j + 1].end(); ++k) {
					results[i][j].insert(*k + n);
					results[i][j].insert(*k - n);
				}
#ifdef DEBUG
				printf("[%d][%d]: %u\n", i, j, results[i][j].size());
				for (set<int>::const_iterator k = results[i][j].begin(); k != results[i][j].end(); ++k)
					printf(" %d", *k);
				putchar('\n');
#endif
			}
		int result  = (2 * N - 1) * n_max;
		for (set<int>::const_iterator k = results[2 * (N - 1)][0].begin(); k != results[2 * (N - 1)][0].end(); ++k)
			result = min(result, abs(*k));
		printf("%d\n", result);
	}
	return 0;
}


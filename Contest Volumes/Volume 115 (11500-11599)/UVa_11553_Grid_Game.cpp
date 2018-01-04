
/*
	UVa 11553 - Grid Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11553_Grid_Game.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

/*
You need to consider all permutation of columns only. Because Bob will choose columns. We do not need to consider permutation of rows. 
Ultimately Alice has to cut all rows and how Bob will cut columns is the main question. Alice's order of row cutting is not important.
*/

int main()
{
	const int n_max = 8, m_min = -1000, m_max = 1000;
	int grid[n_max][n_max], columns[n_max];
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &grid[i][j]);
		for (int i = 0; i < n; i++)
			columns[i] = i;
		int nr_candies_min = m_max * n + 1;
		do {
			int nr_candies = 0;
			for (int i = 0; i < n; i++)
				nr_candies += grid[i][columns[i]];
			nr_candies_min = min(nr_candies_min, nr_candies);
		} while (next_permutation(columns, columns + n));
		printf("%d\n", nr_candies_min);
	}
	return 0;
}


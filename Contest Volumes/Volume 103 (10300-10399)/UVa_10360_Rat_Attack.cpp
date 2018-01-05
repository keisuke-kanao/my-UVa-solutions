
/*
	UVa 10360 - Rat Attack

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10360_Rat_Attack.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_dimensions = 1025;
int grid[nr_dimensions][nr_dimensions];

int main()
{
	int s;
	cin >> s;
	while (s--) {
		int d, n;
		cin >> d >> n;
		memset(grid, 0, sizeof(grid));
		for (int i = 0; i < n; i++) {
			int x, y, p;
			cin >> x >> y >> p;
			for (int j = max(0, x - d); j <= min(x + d, nr_dimensions - 1); j++)
				for (int k = max(0, y - d); k <= min(y + d, nr_dimensions - 1); k++)
					grid[j][k] += p;
		}
		int max_p = -1, max_i, max_j;
		for (int i = 0; i < nr_dimensions; i++)
			for (int j = 0; j < nr_dimensions; j++)
				if (grid[i][j] > max_p) {
					max_p = grid[i][j];
					max_i = i; max_j = j;
				}
		cout << max_i << ' ' << max_j << ' ' << max_p << endl;
	}
	return 0;
}


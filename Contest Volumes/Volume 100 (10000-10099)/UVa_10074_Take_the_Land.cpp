
/*
	UVa 10074 - Take the Land

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10074_Take_the_Land.cpp

	This is a problem similar to the 108 (Maximum Sum) and 10667 (Largest Block).
*/

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

const int n_max = 100;
int array_[n_max][n_max];
int sum[n_max];

int maximum_sum(int m, int n)
{
	int max_sum = numeric_limits<int>::min();
	for (int startx = 0; startx < m; startx++) {
		memset(sum, 0, n * sizeof(int));
		for (int x = startx; x < m; x++) {
			int max_ending_here = 0, max_so_far = numeric_limits<int>::min();
			for (int y = 0; y < n; y++) {
				sum[y] += array_[x][y];
				max_ending_here = max(0, max_ending_here + sum[y]);
				max_so_far = max(max_so_far, max_ending_here);
			}
			max_sum = max(max_sum, max_so_far);
		}
	}
	return max_sum;
}

int main()
{
	while (true) {
		int m, n;
		cin >> m >> n;
		if (!m && !n)
			break;
		int min_t = -m * n;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				int t;
				cin >> t;
				array_[i][j] = (t) ? min_t : 1;
			}
		int max_s = maximum_sum(m, n);
		cout << ((max_s > 0) ? max_s : 0) << endl;
	}
	return 0;
}


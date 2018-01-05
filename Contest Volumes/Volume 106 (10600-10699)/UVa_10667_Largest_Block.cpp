
/*
	UVa 10667 - Largest Block

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10667_Largest_Block.cpp

	This is a problem similar to the 108 (Maximum Sum), 836 (Largest Submatrix), and 10074 (Take the Land).
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

const int n_max = 100;
int array[n_max][n_max];
int sum[n_max];

int maximum_sum(int m, int n)
{
	int max_sum = numeric_limits<int>::min();
	for (int startx = 0; startx < m; startx++) {
		memset(sum, 0, n * sizeof(int));
		for (int x = startx; x < m; x++) {
			int max_ending_here = 0, max_so_far = numeric_limits<int>::min();
			for (int y = 0; y < n; y++) {
				sum[y] += array[x][y];
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
	int p;
	cin >> p;
	while (p--) {
		int n;
		cin >> n;
		int min_t = -n * n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				array[i][j] = 1;
		int b;
		cin >> b;
		while (b--) {
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			for (int i = r1 - 1; i < r2; i++)
				for (int j = c1 - 1; j < c2; j++)
					array[i][j] = min_t;
		}
		cout << maximum_sum(n, n) << endl;
	}
	return 0;
}


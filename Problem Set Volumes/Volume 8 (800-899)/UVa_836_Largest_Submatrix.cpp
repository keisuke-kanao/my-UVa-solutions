
/*
	UVa 836 - Largest Submatrix

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_836_Largest_Submatrix.cpp

	This is a problem similar to the 108 (Maximum Sum), 10074 (Take the Land), and 10667 (Largest Block).
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

const int n_max = 25;
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
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int n = s.length();
		int min_t = -n * n;
		for (int j = 0; j < n; j++)
			array_[0][j] = (s[j] == '1') ? 1 : min_t;
		for (int i = 1; i < n; i++) {
			cin >> s;
			for (int j = 0; j < n; j++)
				array_[i][j] = (s[j] == '1') ? 1 : min_t;
		}
		cout << maximum_sum(n, n) << endl;
		if (t)
			cout << endl;
	}
	return 0;
}


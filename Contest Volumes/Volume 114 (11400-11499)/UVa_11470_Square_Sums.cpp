
/*
	UVa 11470 - Square Sums

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11470_Square_Sums.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 10;
	int grid[n_max][n_max];
	int sums[n_max / 2];
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> grid[i][j];
		for (int w = (n & 1) ? 1 : 2, k = (n - 1) / 2, si = 0; w <= n; w += 2, k--, si++) {
			sums[si] = 0;
			for (int j = k; j < k + w; j++) { // top and bottom lines
				sums[si] += grid[k][j];
				if (w > 1)
					sums[si] += grid[k + w - 1][j];
			}
			for (int i = k + 1; i < k + w - 1; i++) { // left and right sides
				sums[si] += grid[i][k];
				if (w > 1)
					sums[si] += grid[i][k + w - 1];
			}
		}
		cout << "Case " << case_nr << ':';
		for (int i = (n - 1) / 2; i >= 0; i--)
			cout << ' ' << sums[i];
		cout << endl;
	}
	return 0;
}


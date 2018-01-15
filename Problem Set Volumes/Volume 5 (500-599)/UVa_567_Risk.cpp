
/*
	UVa 567 - Risk

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_567_Risk.cpp
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int nr_countries = 20, nr_paths_max = 100;
	// Note that actually, N lines to query the shortest path lengths is more than 100.

bool read_boundaries(int lengths[nr_countries + 1][nr_countries + 1])
{
	for (int i = 1; i <= nr_countries; i++)
		for (int j = 1; j <= nr_countries; j++)
			lengths[i][j] = (i == j) ? 0 : nr_countries;
	for (int i = 1; i <= nr_countries - 1; i++) {
		int j;
		if (cin >> j) {
			while (j--) {
				int k;
				cin >> k;
				lengths[i][k] = lengths[k][i] = 1;
			}
		}
		else
			return false;
	}
	return true;
}

void floyd_warshall(int lengths[nr_countries + 1][nr_countries + 1])
{
	for (int k = 1; k <= nr_countries; k++)
		for (int i = 1; i <= nr_countries; i++)
			for (int j = 1; j <= nr_countries; j++)
				lengths[i][j] = min(lengths[i][j], lengths[i][k] + lengths[k][j]);
}

int main()
{
	for (int t = 1; ; t++) {
		int lengths[nr_countries + 1][nr_countries + 1];
			// lengths[i][j] is the shortest path length between countries i and j
		if (!read_boundaries(lengths))
			break;
		floyd_warshall(lengths);
		cout << "Test Set #" << t << endl;
		int n;
		cin >> n;
		for	(int i = 0; i < n; i++) {
			int j, k;
			cin >> j >> k;
			cout << setfill(' ') << setw(2) << j << " to " << setw(2) << k <<
				": " << lengths[j][k] << endl;
		}
		cout << endl;
	}
	return 0;
}


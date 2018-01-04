
/*
	UVa 356 - Square Pegs And Round Holes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_356_Square_Pegs_And_Round_Holes.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 150;
bool points[n_max + 1][n_max + 1];

int main()
{
	bool printed = false;
	int n;
	while (cin >> n) {
		if (printed)
			cout << endl;
		else
			printed = true;
		for (int x = 0; x <= n; x++)
			for (int y = 0; y <= n; y++)
				points[x][y] = false;
		double dn = static_cast<double>(2 * n - 1) / 2.0;
		double dn_square = dn * dn;
		for (int x = 0; x <= n; x++)
			for (int y = 0; y <= n; y++) {
				double dx = static_cast<double>(x), dy = static_cast<double>(y);
				if (dx * dx + dy * dy <= dn_square)
					points[x][y] = true;
			}
		int nr_border = 0, nr_inside = 0;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++) {
				int nr = 0;
				if (points[x][y])
					nr++;
				if (points[x + 1][y])
					nr++;
				if (points[x][y + 1])
					nr++;
				if (points[x + 1][y + 1])
					nr++;
				if (nr == 4)
					nr_inside++;
				else if (nr)
					nr_border++;
			}
		cout << "In the case n = " << n << ", " << nr_border * 4 <<" cells contain segments of the circle.\n";
		cout << "There are " << nr_inside * 4 << " cells completely contained in the circle.\n";
	}
}


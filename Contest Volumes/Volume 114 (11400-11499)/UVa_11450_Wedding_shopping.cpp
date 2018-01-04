
/*
	UVa 11450 - Wedding shopping

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11450_Wedding_shopping.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int m_max = 200, c_max = 20, k_max = 20;
int shopping[c_max + 1][m_max + 1];
	// shopping[i][j] is the maximum amount of money for i garments and j money

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int m, c;
		cin >> m >> c;
		for (int ci = 1; ci <= c; ci++)
			for (int mi = 1; mi <= m; mi++)
				shopping[ci][mi] = 0;
		bool no_solution = false;
		int min_shopping = 0;
		for (int ci = 1; ci <= c; ci++) {
			int k;
			cin >> k;
			int min_g = -1;
			while (k--) {
				int g;
				cin >> g;
				if (no_solution)
					continue;
				if (min_g == -1)
					min_g = g;
				else
					min_g = min(min_g, g);
				for (int mi = g + min_shopping; mi <= m; mi++)
					shopping[ci][mi] = max(shopping[ci][mi], shopping[ci - 1][mi - g] + g);
			}
			if (no_solution)
				continue;
			min_shopping += min_g;
			no_solution = true;
			for (int mi = min_shopping; mi <= m; mi++)
				if (shopping[ci][mi]) {
					no_solution = false; break;
				}
		}
		if (no_solution)
			cout << "no solution\n";
		else {
			int max_shopping = 0;
			for (int mi = min_shopping; mi <= m; mi++)
				max_shopping = max(max_shopping, shopping[c][m]);
			cout << max_shopping << endl;
		}
	}
	return 0;
}


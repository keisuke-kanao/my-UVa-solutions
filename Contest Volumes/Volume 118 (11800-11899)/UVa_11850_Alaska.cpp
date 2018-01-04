
/*
	UVa 11850 - Alaska

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11850_Alaska.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	const int n_max = 1422;
	int locations[n_max + 1];
	while (true) {
		int i, j, n;
		cin >> n;
		if (!n)
			break;
		for (i = 0; i < n; i++)
			cin >> locations[i];
		sort(locations, locations + n);
		if (locations[n - 1] != n_max) {
			locations[n] = (n_max - locations[n - 1]) * 2 + locations[n - 1];
			n++;
		}
		bool possible = true;
		for (int i = 0; i < n - 1; i++)
			if (locations[i + 1] - locations[i] > 200) {
				possible = false; break;
			}
		cout << ((possible) ? "POSSIBLE\n" : "IMPOSSIBLE\n");
	}
	return 0;
}


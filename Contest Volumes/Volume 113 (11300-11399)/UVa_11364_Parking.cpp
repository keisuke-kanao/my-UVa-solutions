
/*
	UVa 11364 - Parking

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11364_Parking.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int min_p = 99, max_p = 0;
		for (int i = 0; i < n; i++) {
			int p;
			cin >> p;
			min_p = min(min_p, p);
			max_p = max(max_p, p);
		}
		cout << (max_p - min_p) * 2 << endl;
	}
	return 0;
}


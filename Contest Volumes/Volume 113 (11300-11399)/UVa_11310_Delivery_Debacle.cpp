
/*
	UVa 11310 - Delivery Debacle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11310_Delivery_Debacle.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 40;
	int t, n;
	long long nr_ways[n_max + 1];
	nr_ways[0] = nr_ways[1] = 1; nr_ways[2] = 5;
	for (n = 3; n <= n_max; n++) {
		nr_ways[n] = nr_ways[n - 1] + nr_ways[n - 2] * 4 + nr_ways[n - 3] * 2;
#ifdef DEBUG
		cout << nr_ways[n] << endl;
#endif
	}
	cin >> t;
	while (t--) {
		cin >> n;
		cout << nr_ways[n] << endl;
	}
	return 0;
}



/*
	UVa 10664 - Luggage

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10664_Luggage.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int m;
	iss >> m;
	iss.clear();
	while (m--) {
		const int nr_weights_max = 20;
		int weights[nr_weights_max];
		int nr_weights = 0;
		getline(cin, line);
		iss.str(line);
		while (iss >> weights[nr_weights])
			nr_weights++;
		iss.clear();
		sort(weights, weights + nr_weights, greater<int>());
		int one_boot = 0, other_boot = 0;
		for (int i = 0; i < nr_weights; i++) {
			if (one_boot > other_boot)
				other_boot += weights[i];
			else
				one_boot += weights[i];
		}
		cout << ((one_boot == other_boot) ? "YES\n" : "NO\n");
	}
	return 0;
}


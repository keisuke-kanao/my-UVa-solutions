
/*
	UVa 11824 - A Minimum Land Price

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11824_A_Minimum_Land_Price.cpp
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

int main()
{
	const int n_max = 40;
	const int price_max = 5000000;
	int costs[n_max];
	int t;
	cin >> t;
	while (t--) {
		int n = 0;
		while (true) {
			cin >> costs[n];
			if (!costs[n])
				break;
			n++;
		}
		sort(costs, costs + n, greater<int>());
		bool too_expensive = false;
		long long total_price = 0;
		for (int i = 0; i < n; i++) {
			double price = 2.0 * pow(static_cast<double>(costs[i]), static_cast<double>(i + 1));
			if (price > price_max) {
				too_expensive = true; break;
			}
			else {
				total_price += static_cast<long long>(price);
				if (total_price > price_max) {
					too_expensive = true; break;
				}
			}
		}
		if (too_expensive)
			cout << "Too expensive\n";
		else
			cout << total_price << endl;
	}
	return 0;
}


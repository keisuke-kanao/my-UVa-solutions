
/*
	UVa 11369 - Shopaholic

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11369_Shopaholic.cpp
*/

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int n_max = 20000;
int items[n_max];

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> items[i];
		sort(items, items + n, greater<int>());
		int discount = 0;
		for (int i = 2; i < n; i += 3)
			discount += items[i];
		cout << discount << endl;
	}
	return 0;
}


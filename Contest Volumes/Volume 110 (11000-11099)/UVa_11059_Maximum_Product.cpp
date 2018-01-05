
/*
	UVa 11059 - Maximum Product

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11059_Maximum_Product.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	const int n_max = 18;
	int sequence[n_max];
	int n, c = 1;
	while (cin >> n) {
		for (int i = 0; i < n; i++)
			cin >> sequence[i];
		long long max_s = 0;
		for (int i = 0; i < n; i++) {
			long long s = sequence[i];
			max_s = max(s, max_s);
			for (int j = i + 1; j < n; j++) {
				s *= sequence[j];
				max_s = max(max_s, s);
			}
		}
		cout << "Case #" << c << ": The maximum product is " << max_s << ".\n\n";
		c++;
	}
	return 0;
}


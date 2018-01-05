
/*
	UVa 10365 - Blocks

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10365_Blocks.cpp
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
		int min_area = 2 * (n * 1 + 1 * 1 + 1 * n);
		for (int w = 1; w <= n; w++)
			for (int h = w; h <= n; h++) {
				int s = w * h;
				if (s > n)
					break;
				if (!(n % s)) {
					int d = n / s;
					min_area = min(min_area, 2 * (w * h + h * d + d * w));
				}
			}
		cout << min_area << endl;
	}
	return 0;
}


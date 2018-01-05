
/*
	UVa 11342 - Three-square

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11342_Three_square.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int sqrt_n = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
		bool possible = false;
		int a, b, c, sqr_c;
		for (a = 0; a <= sqrt_n; a++) {
			for (b = a; b <= sqrt_n; b++)
				if ((sqr_c = n - a * a - b * b) >= 0) {
					c = static_cast<int>(sqrt(static_cast<double>(sqr_c)));
					if (c >= b && c * c == sqr_c) {
						possible = true; break;
					}
				}
			if (possible)
				break;
		}
		if (possible)
			cout << a << ' ' << b << ' ' << c << endl;
		else
			cout << -1 << endl;
	}
	return 0;
}



/*
	UVa 10920 - Spiral Tap

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10920_Spiral_Tap.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	while (true) {
		int sz;
		long long p;
		cin >> sz >> p;
		if (!sz && !p)
			break;
		long long x = (sz + 1) / 2, y = (sz + 1) / 2;
		long long q = sqrt(static_cast<double>(p));
			// max. odd number equal to or less than sqrt(p)
		if (!(q & 1))
			q--;
		x += (q - 1) / 2; y += (q - 1) / 2;
		p -= q * q;
		if (p) {
			q++;
			if (p <= q) {
				x -= p - 1; y++;
			}
			else if (p <= q * 2) {
				x -= q - 1; y -= p - q - 1;
			}
			else if (p <= q * 3) {
				x -= q * 3 - p - 1; y -= q - 1;
			}
			else {
				x++; y -= q * 4 - p - 1;
			}
		}
		cout << "Line = " << y << ", column = " << x << ".\n";
	}
	return 0;
}


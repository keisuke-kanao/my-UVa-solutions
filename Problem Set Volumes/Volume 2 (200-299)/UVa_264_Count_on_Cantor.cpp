
/*
	UVa 264 - Count on Cantor

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_264_Count_on_Cantor.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		int m = static_cast<int>((-1.0 + sqrt(1.0 + static_cast<double>(n) * 8.0)) / 2.0);
		int s = (m * (m + 1)) / 2;
		int denominator, numerator;
		if (s == n) {
			if (m & 1) {
				denominator = m; numerator = 1;
			}
			else {
				denominator = 1; numerator = m;
			}
		}
		else {
			m++;
			int d = n - s;
			if (m & 1) {
				denominator = 0; numerator = m + 1;
				denominator += d; numerator -= d;
			}
			else {
				denominator = m + 1; numerator = 0;
				denominator -= d; numerator += d;
			}
		}
		cout << "TERM " << n << " IS " << numerator << '/' << denominator << endl;
	}
	return 0;
}


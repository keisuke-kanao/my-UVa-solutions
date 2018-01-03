
/*
	UVa 880 - Cantor Fractions

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_880_Cantor_Fractions.cpp

	This problem is similar to 264 - Count on Cantor.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	long long n;
	while (cin >> n) {
		long long m = static_cast<long long>((-1.0 + sqrt(1.0 + static_cast<double>(n) * 8.0)) / 2.0);
		long long s = (m * (m + 1)) / 2;
		long long denominator, numerator;
		if (s == n) {
			denominator = m; numerator = 1;
		}
		else {
			denominator = 0; numerator = m + 2;
			long long d = n - s;
			denominator += d; numerator -= d;
		}
		cout << numerator << '/' << denominator << endl;
	}
	return 0;
}


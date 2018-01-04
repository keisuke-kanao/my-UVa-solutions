
/*
	UVa 11621 - Small Factors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11621_Small_Factors.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	const double log2 = log10(2.0), log3 = log10(3.0);
	while (true) {
		long long m;
		cin >> m;
		if (!m)
			break;
		int p2 = log10(static_cast<double>(m)) / log2;
		if (pow(2.0, static_cast<double>(p2)) < m)
			p2++;
		long long c23 = static_cast<long long>(pow(2.0, static_cast<double>(p2)));
		for ( ; p2 >= 0; p2--) {
			long long p = static_cast<long long>(pow(2.0, static_cast<double>(p2)));
			long long n = m / p;
			if (n * p > m)
				n++;
			int p3 = log10(static_cast<double>(n)) / log3;
			if (pow(3.0, static_cast<double>(p3)) < n)
				p3++;
			long long c = p * static_cast<long long>(pow(3.0, static_cast<double>(p3)));
			if (c >= m && c < c23) {
				c23 = c;
				if (c == m)
					break;
			}
		}
		cout << c23 << endl;
	}
	return 0;
}


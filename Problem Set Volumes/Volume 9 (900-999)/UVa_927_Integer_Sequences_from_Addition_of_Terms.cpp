
/*
	UVa 927 - Integer Sequences from Addition of Terms

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_927_Integer_Sequences_from_Addition_of_Terms.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int C;
	cin >> C;
	while (C--) {
		const int nr_degrees_max = 20;
		int nr_degrees, coefficients[nr_degrees_max + 1], d, k;
		cin >> nr_degrees;
		for (int i = 0; i <= nr_degrees; i++)
			cin >> coefficients[i];
		cin >> d >> k;
		int n = 1;
		while (k > n * d) {
			k -= n * d;
			n++;
		}
		long long m = 1, a = 0;
		for (int i = 0; i <= nr_degrees; i++, m *= n)
			a += coefficients[i] * m;
		cout << a << endl;
	}
	return 0;
}


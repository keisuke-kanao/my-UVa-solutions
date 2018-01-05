
/*
	UVa 10302 - Summation of Polynomials

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10302_Summation_of_Polynomials.cpp
*/

#include <iostream>
using namespace std;

/*
	Σk^3 (k = 1 to n) = (n * (n + 1) / 2)^2
*/

int main()
{
	long long x;
	while (cin >> x) {
		x *= x + 1;
		x >>= 1;
		x *= x;
		cout << x << endl;
	}
	return 0;
}



/*
	UVa 113 - Power of Cryptography

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_113_Power_of_Cryptography.cpp

	An accepted solution.
*/

/*
	For k^n = p, getting the logarithm of both sides results in:
		n * log(k) = log(p).
		k = exp(log(p) / n).

	Or,

	For k^n = p,
		k = p^(1 / n) = pow(p, 1 / n)
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	double n;
	while (cin >> n) {
		double p;
		cin >> p;
		printf("%.lf\n", pow(p, 1 / n));
	}
	return 0;
}


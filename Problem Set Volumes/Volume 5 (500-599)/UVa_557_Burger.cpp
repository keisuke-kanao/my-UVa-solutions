
/*
	UVa 557 - Burger

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_557_Burger.cpp
*/

#include <iostream>
#include <cstdio>
using namespace std;

/*
	Let p(n) be the probability that Ben and Bill get the same type of burger for n guests, then:
		p(n) = 1.0 - C(n - 2, (n - 2) / 2) / 2^(n - 2).
	Here, C(n, k) is the number of k-combinations from a given set S of n elements.
	Let pf(n) =  C(n - 2, (n - 2) / 2) / 2^(n - 2).
	Then, using pf(n - 2), pf(n), pfn(n) can be calculated recursively as below:
		pf(n) = {(n - 3) / (n - 2)} * pf(n - 2).
		pf(2) = 1.0;
*/

const int n_max = 100000; // max. number of guests
double pf[1 + n_max / 2];

int main()
{
	pf[1] = 1.0;
	for (int i = 2; i <= n_max / 2; i++)
		pf[i] = pf[i - 1] * static_cast<double>(2 * i - 3) / static_cast<double>(2 * i - 2);
	int nr_problems;
	cin >> nr_problems;
	while (nr_problems--) {
		int n;
		cin >> n;
		printf("%.4lf\n", 1.0 - pf[n / 2]);
	}
	return 0;
}


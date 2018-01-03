
/*
	UVa 884 - Factorial Factors

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_884_Factorial_Factors.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

const int n_max = 1000000;
int nr_factors[n_max + 1]; // nr_factors[i] is the number of factors for i!

int count_factors(int n)
{
	int nr = 0;
	for ( ; !(n & 1); n >>= 1)
		nr++;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			nr++;
			n /= i;
		}
		else
			i += 2;
	}
	if (n > 1)
		nr++;
	return nr;
}

int main()
{
	for (int i = 2; i <= n_max; i++)
		nr_factors[i] = nr_factors[i - 1] + count_factors(i);
	int n;
	while (cin >> n)
		cout << nr_factors[n] << endl;
	return 0;
}


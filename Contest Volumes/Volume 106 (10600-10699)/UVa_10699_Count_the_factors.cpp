
/*
	UVa 10699 - Count the factors

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10699_Count_the_factors.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int count_factors(int n)
{
	int nr_factors = 0;
	bool different_prime = true;
	for ( ; !(n & 1); n >>= 1) {
		if (different_prime) {
			different_prime = false;
			nr_factors++;
		}
	}
	different_prime = true;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			if (different_prime) {
				different_prime = false;
				nr_factors++;
			}
			n /= i;
		}
		else {
			i += 2;
			different_prime = true;
		}
	}
	if (n > 1 && different_prime)
		nr_factors++;
	return nr_factors;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << n << " : " << count_factors(n) << endl;
	}
}


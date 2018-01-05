
/*
	UVa 10738 - Riemann vs Mertens

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10738_Riemann_vs_Mertens.cpp
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

const int n_max = 1000000, sqrt_n_max = 1000;
int mu[n_max + 1], M[n_max + 1];
bool primes[sqrt_n_max + 1];

bool prime_factorization(int n, int& nr)
{
	nr = 0;
	memset(primes, 0, sizeof(primes));
	for ( ; !(n & 1); n >>= 1) {
		if (primes[2])
			return false;
		primes[2] = true;
		nr++;
	}
	for (int i = 3, e = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= e; ) {
		if (!(n % i)) {
			if (primes[i])
				return false;
			primes[i] = true;
			nr++;
			n /= i;
			e = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
		}
		else
			i += 2;
	}
	if (n > 1) {
		if (n <= sqrt_n_max && primes[n])
			return false;
		nr++;
	}
	return true;
}

int main()
{
	mu[1] = M[1] = 1;
	for (int i = 2, nr = 0; i <= n_max; i++) {
		if (prime_factorization(i, nr))
			mu[i] = (nr & 1) ? -1 : 1;
		M[i] += M[i - 1] + mu[i];
	}
#ifdef DEBUG
	cout << mu[n_max] << ' ' << M[n_max] << endl;
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << setfill(' ') << setw(8) << n << setw(8) << mu[n] << setw(8) << M[n] << endl;
	}
	return 0;
}


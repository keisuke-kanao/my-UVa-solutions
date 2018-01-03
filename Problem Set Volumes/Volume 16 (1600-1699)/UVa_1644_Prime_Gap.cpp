
/*
	UVa 1644 - Prime Gap

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1644_Prime_Gap.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int n_max = 1299709, nr_primes = 100000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int primes[nr_primes];

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int main()
{
	sieve_of_eratosthenes();
	for (int i = 2, j = 0; i <= n_max; i++)
		if (!not_primes[i])
			primes[j++] = i;
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int gap = 0;
		if (not_primes[n]) {
			int i = upper_bound(primes, primes + nr_primes, n) - primes;
			gap = primes[i] - primes[i - 1];
		}
		printf("%d\n", gap);
	}
	return 0;
}


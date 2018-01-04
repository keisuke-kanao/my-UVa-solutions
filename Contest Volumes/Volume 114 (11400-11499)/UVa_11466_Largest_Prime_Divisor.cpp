
/*
	UVa 11466 - Largest Prime Divisor

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11466_Largest_Prime_Divisor.cpp
*/

#include <cstdio>
#include <cmath>
using namespace std;

const int n_max = 10000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime

const int nr_primes = 664579;
int primes[nr_primes];

void sieve_of_eratosthenes()
{
	not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

long long prime_factorization(long long n)
{
	if (n < 0)
		n = -n;
	int nr_p = 0;
	long long max_p = 0;
	if (!(n & 1)) {
		nr_p++;
		max_p = 2;
		do
			n >>= 1;
		while (!(n & 1));
	}
	for (int pi = 1, e = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); pi < nr_primes && primes[pi] <= e; ) {
		int p = primes[pi];
		if (!(n % p)) {
			if (max_p != p) {
				nr_p++;
				max_p = p;
			}
			n /= p;
			e = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
		}
		else
			pi++;
	}
	if (n > 1 && max_p != n) {
		nr_p++;
		max_p = n;
	}
	return (nr_p > 1) ? max_p : -1;
}

int main()
{
	sieve_of_eratosthenes();
	for (int i = 2, j = 0; i <= n_max; i++)
		if (!not_primes[i])
			primes[j++] = i;
#ifdef DEBUG
	printf("%d\n", primes[nr_primes - 1]);
#endif
	while (true) {
		long long n;
		scanf("%lld", &n);
		if (!n)
			break;
		printf("%lld\n", prime_factorization(n));
	}
	return 0;
}


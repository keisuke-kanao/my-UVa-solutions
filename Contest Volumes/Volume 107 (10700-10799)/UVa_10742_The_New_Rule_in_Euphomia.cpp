
/*
	UVa 10742 - The New Rule in Euphomia

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10742_The_New_Rule_in_Euphomia.cpp
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;

const int n_max = 1000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int nr_primes, primes[n_max]; // primes[i] is the i-th prime number
long long nr_ways[n_max + 1]; // nr_ways[primes[i]] is the number of ways for prime number i

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int main()
{
	sieve_of_eratosthenes();
	long long m = 0, s = 0;
	for (int i = 2; i <= n_max; i++)
		if (!not_primes[i]) {
			primes[nr_primes++] = i;
			s += m++;
			nr_ways[i] = s;
		}
	primes[nr_primes++] = n_max; // sentinel
#ifdef DEBUG
	printf("%d %d %lld\n", nr_primes, primes[nr_primes - 1], nr_ways[primes[nr_primes - 1]]);
	for (int i = 0; primes[i] < 100; i++)
		printf("%d %lld\n", primes[i], nr_ways[primes[i]]);
#endif
	for (int case_nr = 1; ; case_nr++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		long long nr = 0;
		// locate the largest prime that is less than (n - 1)
		int i = distance(primes, lower_bound(primes, primes + nr_primes, n - 2));
		if (primes[i] > n - 2)
			i--;
		for ( ; i > 0 && n - primes[i] < primes[i - 1]; i--) {
			// locate the largest prime that is equal to or less than (n - primes[i])
			int j = distance(primes, lower_bound(primes, primes + nr_primes, n - primes[i]));
			if (primes[j] > n - primes[i])
				j--;
			if (j > 0)
				nr += nr_ways[primes[j]] - nr_ways[primes[j - 1]] + 1;
			else if (j == 0)
				nr++;
#ifdef DEBUG
			if (j >= 0)
				printf("%d %d, %lld\n", primes[i], primes[j], nr);
			else
				printf("%d, %lld\n", primes[i], nr);
#endif
		}
		if (i > 0)
			nr += nr_ways[primes[i]];
		printf("Case %d: %lld\n", case_nr, nr);
	}
	return 0;
}


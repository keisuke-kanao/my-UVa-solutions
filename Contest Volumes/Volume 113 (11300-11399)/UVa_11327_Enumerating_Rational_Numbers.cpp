
/*
	UVa 11327 - Enumerating Rational Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11327_Enumerating_Rational_Numbers.cpp
*/

#include <algorithm>
#include <iterator>
#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 200000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int phis[n_max + 1]; // phis[i] is Euler's totient (or phi) function's values, i.e., 
	// number the positive integers up to a given number i that are relatively prime to i
long long sum_of_phis[n_max + 1]; // sum_of_phits[i] is the sum of phis[j] where j is from 0 up to i

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	phis[0] = 1;
	for (int i = 1; i <= n_max; i++)
		phis[i] = i;
	for (int i = 1; i <= n_max; i++)
        if (!not_primes[i])
			for (int j = i; j <= n_max; j += i)
				phis[j] -= phis[j] / i;
	sum_of_phis[0] = 1;
	for (int i = 1; i <= n_max; i++)
		sum_of_phis[i] = sum_of_phis[i - 1] + phis[i];
#ifdef DEBUG
	printf("%lld\n", sum_of_phis[n_max]);
#endif
	while (true) {
		long long k;
		scanf("%lld", &k);
		if (!k)
			break;
		int d = distance(sum_of_phis, lower_bound(sum_of_phis, sum_of_phis + n_max, k)), n = 0;
		if (d) {
			k -= sum_of_phis[d - 1];
			for (n++; ; n++)
				if (gcd(n, d) == 1 && !--k)
					break;
		}
		else
			d = 1;
		printf("%d/%d\n", n, d);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}


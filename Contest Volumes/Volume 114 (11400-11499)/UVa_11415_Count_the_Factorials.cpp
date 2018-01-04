
/*
	UVa 11415 - Count the Factorials

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11415_Count_the_Factorials.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 10000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int multiplicities[n_max + 1];

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
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	int m = 2;
	for (int count = 0; m <= n_max && count <= n_max; m++) {
		if (!not_primes[m]) {
			for (long long j = m; j <= n_max; j *= m)
				for (long long k = j; k <= n_max; k += j)
					multiplicities[k]++;
		}
		count += multiplicities[m];
		multiplicities[m] = count;
	}
#ifdef DEBUG
	printf("%d: %d\n", m - 1, multiplicities[m - 1]);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", upper_bound(multiplicities, multiplicities + m, n) - multiplicities);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}


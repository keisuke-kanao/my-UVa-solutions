/*
	UVa 10871 - Primed Subsequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10871_Primed_Subsequence.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 10000, nr_max = 1000000;
bool not_primes[nr_max + 1]; // not_primes[i] is true if i is not a prime
int numbers[n_max];
int partial_sums[n_max]; // partial_sums[i] is the sum of numbers[] up to i

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(nr_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= nr_max; j += i)
				not_primes[j] = true;
		}
}

int get_partial_sum(int i, int j)
{
	int ps = partial_sums[j];
	if (i)
		ps -= partial_sums[i - 1];
	return ps;
}

bool is_prime(int n)
{
	if (n <= nr_max)
		return !not_primes[n];
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int i, x, n;
		scanf("%d", &n);
		int ps = 0;
		for (i = 0; i < n; i++) {
			scanf("%d", &numbers[i]);
			ps += numbers[i];
			partial_sums[i] = ps;
		}
		for (x = 1; x < n; x++) {
			for (i = 0; i < n - x; i++)
				if (is_prime(get_partial_sum(i, i + x)))
					break;
			if (i < n - x)
				break;
		}
		if (x < n) {
			printf("Shortest primed subsequence is length %d:", x + 1);
			for ( ; x >= 0; i++, x--)
				printf(" %d", numbers[i]);
			putchar('\n');
		}
		else
			puts("This sequence is anti-primed.");
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}


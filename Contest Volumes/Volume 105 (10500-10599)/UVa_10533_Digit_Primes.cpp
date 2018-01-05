
/*
	UVa 10533 - Digit Primes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10533_Digit_Primes.cpp
*/

#include <cstdio>
#include <cmath>

const int n_max = 1000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int nr_digit_primes[n_max + 1]; // nr_digit_primes[i] is the number of digit primes between 1 and i

void sieve_of_eratosthenes()
{
	not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int sum_of_digits(int n)
{
	int s = 0;
	for ( ; n; n /= 10)
		s += n % 10;
	return s;
}

int main()
{
	sieve_of_eratosthenes();
	int nr = 1;
	nr_digit_primes[2] = nr;
	for (int i = 3; i <= n_max; i += 2) {
		if (!not_primes[i] && !not_primes[sum_of_digits(i)])
			nr++;
		nr_digit_primes[i] = nr_digit_primes[i + 1] = nr;
	}
	int n;
	scanf("%d", &n);
	while (n--) {
		int t1, t2;
		scanf("%d %d", &t1, &t2);
		printf("%d\n", nr_digit_primes[t2] - nr_digit_primes[t1 - 1]);
	}
	return 0;
}


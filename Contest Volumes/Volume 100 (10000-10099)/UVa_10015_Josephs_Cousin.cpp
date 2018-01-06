
/*
	UVa 10015 - Joseph's Cousin

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10015_Josephs_Cousin.cpp
*/

#include <iostream>
#include <cstring>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 3501, nr_primes_max = 500000;
int people[n_max];
bool not_primes[nr_primes_max + 1]; // not_primes[i] is true if i is not a prime
	// There are 41538 prime numbers that are equal to or less than 500000.
int primes[n_max];

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(nr_primes_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= nr_primes_max; j += i)
				not_primes[j] = true;
		}
}

int get_next_prime(int n)
{
	for (n++; ; n++)
		if (!not_primes[n])
			return n;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	int nr_primes = 0;
	for (int i = 2, j = 0; j < n_max; i++)
		if (!not_primes[i])
			primes[j++] = i;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			people[i] = i + 1;
		for (int i = 0, j = 0; n > 1; n--, j++) {
			i = (i + primes[j] - 1) % n;
#ifdef DEBUG
			cout << people[i] << ' ' << m << endl;
#endif
			memmove(&people[i], &people[i + 1], sizeof(int) * (n - i - 1));
		}
		cout << people[0] << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}



/*
	UVa 10311 - Goldbach and Euler

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10311_Goldbach_and_Euler.cpp
*/

#include <iostream>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 100000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime

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
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	int n;
	while (cin >> n) {
		bool sum_of_two_primes = false;
		int p1 = 1, p2 = 0;
		if (n < 5)
			;
		else if (n & 1) { // n is an odd number
			if (!not_primes[n - 2]) {
				p1 = 2; p2 = n - 2;
			}
		}
		else { // n is an even number
			int p = n >> 1; // n / 2
			if (!(p & 1)) // p is an even number
				p--;
			else
				p -= 2;
			for ( ; p > 1; p -= 2)
				if (!not_primes[p] && !not_primes[n - p]) {
					p1 = p; p2 = n - p;
					break;
				}
		}
		if (p2 > p1)
			cout << n << " is the sum of " << p1 << " and " << p2 << ".\n";
		else
			cout << n << " is not the sum of two primes!\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


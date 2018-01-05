
/*
	UVa 10236 - The Fibonacci Primes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10236_The_Fibonacci_Primes.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef DEBUG
#include <cassert>
#endif

/*
serial: 	0  1  2  3  4  5  6   7   8   9  10  11  12  13  14  15  16   17   18   19   20
Fibonacci:	0  1  1  2  3  5  8  13  21  34  55  89 144 233	377	610	987	1597 2584 4181 6765
    Prime:           *  *  *      *               *       *                *         *
*/

const int N_max = 22000, n_max = 249439;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int serials[N_max + 1];
double fibs[n_max + 1];

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
	not_primes[4] = false;
	for (int n = 3, s = 0; n <= n_max; n++)
		if (!not_primes[n]) {
			serials[++s] = n;
#ifdef DEBUG
			assert(s <= N_max);
#endif
		}
	fibs[1] = fibs[2] = 1.0;
	bool flag = false;
	for (int i = 3; i <= n_max; i++) {
		fibs[i] = fibs[i - 1] + ((flag) ? fibs[i - 2] / 10.0 : fibs[i - 2]);
		flag = false;
		while (fibs[i] >= 1000000000.0) {
			fibs[i] /= 10.0;
			flag = true;
		}
	}
	int s;
	while (scanf("%d", &s) != EOF)
		printf("%lld\n", static_cast<long long>(floor(fibs[serials[s]])));
	return 0;
}


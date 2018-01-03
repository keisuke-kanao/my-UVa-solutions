
/*
	UVa 1246 - Find Terrorists

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1246_Find_Terrorists.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int n_max = 10000, max_nr_divisors = 64;
int nr_divisors[n_max + 1];
bool not_primes[max_nr_divisors + 1]; // not_primes[i] is true if i is not a prime
bool nr_divisors_primes[n_max + 1];

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(max_nr_divisors))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= max_nr_divisors; j += i)
				not_primes[j] = true;
		}
}

int main()
{
	sieve_of_eratosthenes();
	for (int i = 1; i <= n_max; i++)
		for (int j = i; j <= n_max; j += i)
			nr_divisors[j]++;
	for (int i = 2; i <= n_max; i++)
		nr_divisors_primes[i] = !not_primes[nr_divisors[i]];
	int T;
	scanf("%d", &T);
	while (T--) {
		int L, H;
		scanf("%d %d", &L, &H);
		bool printed = false;
		for (int i = L; i <= H; i++)
			if (nr_divisors_primes[i]) {
				if (printed)
					putchar(' ');
				else
					printed = true;
				printf("%d", i);
			}
		if (printed)
			putchar('\n');
		else
			puts("-1");
	}
	return 0;
}


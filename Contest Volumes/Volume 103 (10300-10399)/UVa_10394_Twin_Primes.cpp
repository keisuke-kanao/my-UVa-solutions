
/*
	UVa 10394 - Twin Primes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10394_Twin_Primes.cpp
*/

#include <iostream>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 20000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
const int nr_twin_primes_max = 100000;
int twin_primes[nr_twin_primes_max + 1]; // twin_prims[i] is the smaller prime of i-th twin prime pair

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
	twin_primes[1] = 3;
/*
	twin_primes[2] = 5; twin_primes[3] = 11; twin_primes[4] = 17;
	twin_primes[5] = 29; twin_primes[6] = 41;
*/
	for (int i = 2; i <= nr_twin_primes_max; i++) {
		int j = twin_primes[i - 1] + 2;
		while (true) {
			if (!not_primes[j + 2])
				break;
			else {
				do
					j += 2;
				while (not_primes[j]);
			}
		}
		twin_primes[i] = j;
	}
#ifdef DEBUG
	cout << twin_primes[nr_twin_primes_max] << endl;
#endif
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	int s;
	while (cin >> s)
		cout << '(' << twin_primes[s] << ", " << twin_primes[s] + 2 << ")\n";
	return 0;
}


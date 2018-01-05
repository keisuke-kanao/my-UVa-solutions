
/*
	UVa 11086 - Composite Prime

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11086_Composite_Prime.cpp
*/

/*
4
3 4 6 8

3				3 is a prime number
4 = 2 * 2
6 = 2 * 3
8 = 2 * 4		4 is an element in M

5
12 13 21 22 23

12 = 3 * 4		4 is an element in M
13				13 is a prime number
21 = 3 * 7
22 = 3 * 11
23				23 is a prime number
*/

#include <iostream>
#include <cmath>
using namespace std;

const int n_max = 1048576;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
bool not_composite_primes[n_max + 1]; // composite_primes[i] is true if i is not a composite prime

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

void composite_primes()
{
	not_composite_primes[0] = not_composite_primes[1] = not_composite_primes[2] = not_composite_primes[3] = true;
	for (int i = 4; i <= n_max; i++)
		if (not_primes[i] && !not_composite_primes[i]) {
			for (int j = i * 2; j <= n_max; j += i)
				not_composite_primes[j] = true;
		}
}

int main()
{
	sieve_of_eratosthenes();
	composite_primes();
#ifdef DEBUG
	int nr_composite_primes = 0;
	for (int i = 4; i <= n_max; i++)
		if (not_primes[i] && !not_composite_primes[i])
			nr_composite_primes++;
	cout << nr_composite_primes << endl; // 219759
#endif
	int K;
	while (cin >> K) {
		int nr = 0;
		while (K--) {
			int n;
			cin >> n;
			if (not_primes[n] && !not_composite_primes[n])
				nr++;
		}
		cout << nr << endl;
	}
	return 0;
}


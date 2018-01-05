
/*
	UVa 10852 - Less Prime

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10852_Less_Prime.cpp
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

const int n_max = 10000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime

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
	int m, n;
	cin >> m;
	while (m--) {
		cin >> n;
		int x = 2, max_d = n - (n / 2) * 2;
		for (int i = 3; i <= n; i += 2)
			if (!not_primes[i]) {
				int d = n - (n / i) * i;
				if (d > max_d) {
					x = i; max_d = d;
				}
			}
		cout << x << endl;
	}
	return 0;
}


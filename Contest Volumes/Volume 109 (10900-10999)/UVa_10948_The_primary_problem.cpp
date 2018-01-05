
/*
	UVa 10948 - The primary problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10948_The_primary_problem.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

const int n_max = 1000000;
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
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << n << ":\n";
		if (!not_primes[n - 2])
			cout << 2 << '+' << n - 2 << endl;
		else {
			int i = 3, j = n / 2;
			for (i = 3; i <= j; i += 2)
				if (!not_primes[i] && !not_primes[n - i])
					break;
			if (i <= j)
				cout << i << '+' << n - i << endl;
			else
				cout << "NO WAY!\n";
		}
	}
	return 0;
}


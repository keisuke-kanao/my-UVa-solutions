
/*
	UVa 1210 - Sum of Consecutive Prime Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1210_Sum_of_Consecutive_Prime_Numbers.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int n_max = 10000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
vector<int> primes; // prime numbers
int nr_reps[n_max + 1]; // nr_reps[i] is the number of representations of i

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
	sieve_of_eratosthenes();
	for (int i = 2; i <= n_max; i++)
		if (!not_primes[i])
			primes.push_back(i);
	for (int i = 0, e = static_cast<int>(primes.size()); i < e; i++) {
		int p = primes[i];
		nr_reps[p]++;
		for (int j = i - 1; j >= 0; j--) {
			p += primes[j];
			if (p > n_max)
				break;
			nr_reps[p]++;
		}
	}
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << nr_reps[n] << endl;
	}
	return 0;
}


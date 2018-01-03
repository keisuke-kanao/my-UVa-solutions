
/*
	UVa 897 - Anagrammatic Primes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_897_Anagrammatic_Primes.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

const int n_max = 10000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
const int pow_10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
vector<int> anagrammatic_primes;

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

bool is_anagrammatic_prime(int n)
{
	if (not_primes[n])
		return false;
	char digits[8];
	int dn = 0;
	do {
		digits[dn++] = n % 10 + '0';
		n /= 10;
	} while (n);
	digits[dn] = '\0';
	sort(digits, digits + dn);
	do {
		if (not_primes[atoi(digits)])
			return false;
	} while (next_permutation(digits, digits + dn));
	return true;
}

int main()
{
	sieve_of_eratosthenes();
	for (int i = 2; i <= n_max; i++)
		if (is_anagrammatic_prime(i))
			anagrammatic_primes.push_back(i);
	size_t ap_max = anagrammatic_primes.size();
#ifdef DEBUG
	for (size_t i = 0; i < ap_max; i++) {
		if (i)
			cout << ' ';
		cout << anagrammatic_primes[i];
	}
	cout << endl;
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int ap = 0, nh = pow_10[static_cast<int>(log10(static_cast<double>(n)) + 1.0)];
		for (size_t i = 0; i < ap_max; i++) {
			if (anagrammatic_primes[i] >= nh)
				break;
			if (anagrammatic_primes[i] > n) {
				ap = anagrammatic_primes[i]; break;
			}
		}
		cout << ap << endl;
	}
	return 0;
}


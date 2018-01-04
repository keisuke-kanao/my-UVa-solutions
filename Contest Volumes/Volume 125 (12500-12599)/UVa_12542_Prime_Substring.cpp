
/*
	UVa 12542 - Prime Substring

	To build using Visual Studio 2012
		cl -EHsc -O2 UVa_12542_Prime_Substring.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int n_max = 100000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

const int nr_digits_max = 255, nr_prime_digits_max = 6;

int number(const char* s, int i, int j)
{
	int n = 0;
	for ( ; i < j; i++) {
		n *= 10;
		n += s[i] - '0';
	}
	return n;
}

int main()
{
	sieve_of_eratosthenes();
	while (true) {
		char s[nr_digits_max + 1];
		scanf("%s", s);
		int length = strlen(s);
		if (length == 1 && s[0] == '0')
			break;
		int max_prime = 0;
		for (int i = 0; i < length; i++)
			for (int j = i + 1; j <= i + nr_prime_digits_max && j <= length; j++) {
				int n = number(s, i, j);
				if (n <= n_max && !not_primes[n] && n > max_prime)
					max_prime = n;
			}
		printf("%d\n", max_prime);
	}
	return 0;
}


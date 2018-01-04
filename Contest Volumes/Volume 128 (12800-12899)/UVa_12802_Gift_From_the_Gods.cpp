
/*
	UVa 12802 - Gift From the Gods

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12802_Gift_From_the_Gods.cpp
*/

#include <cstdio>
#include <cmath>
#include <cstring>

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

bool is_palindrome_prime(int n)
{
	if (not_primes[n])
		return false;
	int length = 0;
	char s[8];
	do {
		s[length++] = n % 10;
		n /= 10;
	} while (n);
	for (int i = 0, j = length - 1; i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
/*
	const int pow10s[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
	int nr_digits = static_cast<int>(log10(static_cast<double>(n)) + 1.0);
	int r = 0;
	for (int i = 0, j = nr_digits - 1, nn = n; i < nr_digits; i++, j--) {
		int k = nn / pow10s[j] * pow10s[i];
		r += k;
		nn -= k;
	}
	return n == r;
*/
}

int main()
{
	sieve_of_eratosthenes();
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%d\n", n * 2);
		if (is_palindrome_prime(n))
			break;
	}
	return 0;
}


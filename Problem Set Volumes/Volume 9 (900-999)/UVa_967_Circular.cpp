
/*
	UVa 967 - Circular

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_967_Circular.cpp
*/

#include <cstdio>
#include <cmath>

const int n_max = 1000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int nr_circular_primes[n_max + 1]; // nr_circular_primes[i] is the number of circular primes up to i

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int get_number(int length, int* digits)
{
	int n = 0;
	for (int i = 0; i < length; i++, digits++) {
		if (i)
			n *= 10;
		n += *digits;
	}
	return n;
}

bool is_circular_prime(int n)
{
	if (not_primes[n])
		return false;
	const int nr_digits_max = 8;
	int digits[nr_digits_max * 2];
	int length;
	for (length = 1; ; length++) {
		digits[nr_digits_max - length] = n % 10;
		n /= 10;
		if (!n)
			break;
	}
	for (int i = nr_digits_max - length, j = nr_digits_max, k = length - 1; k; k--) {
		digits[j++] = digits[i++];
		if (not_primes[get_number(length, &digits[i])])
			return false;
	}
	return true;
}

int main()
{
	sieve_of_eratosthenes();
	int nr = 0;
	for (int n = 100; n <= n_max; n++) {
		if (is_circular_prime(n))
			nr++;
		nr_circular_primes[n] = nr;
	}
	while (true) {
		int i, j;
		scanf("%d", &i);
		if (i == -1)
			break;
		scanf("%d", &j);
		nr = nr_circular_primes[j] - nr_circular_primes[i - 1];
		if (!nr)
			puts("No Circular Primes.");
		else if (nr == 1)
			puts("1 Circular Prime.");
		else
			printf("%d Circular Primes.\n", nr);
	}
	return 0;
}



/*
	7.6.5 Summation of Four Primes
	PC/UVa IDs: 110705/10168, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10168_Summation_of_Four_Primes.cpp
*/

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int n_max = 10000000;

unsigned char* generate_primes()
{
	int size = (n_max + 1 + 7) / 8;
	unsigned char* primes = new unsigned char[size];
	memset(primes, -1, size); // set all bits
	primes[0] &= ~3;
	for (int i = 2; i < static_cast<int>(sqrt(static_cast<double>(n_max))) + 2; i++)
		if (primes[i / 8] & (1 << i % 8)) {
			for (int j = i + i; j < n_max + 1; j += i)
				primes[j / 8] &= ~(1 << j % 8);
		}
	return primes;
}

bool is_prime(int n, const unsigned char* are_primes)
{
	return are_primes[n / 8] & (1 << n % 8);
}

bool sum_of_two_primes(int n, int* primes, const unsigned char* are_primes)
{
	if (is_prime(n - 2, are_primes)) {
		*primes++ = 2; *primes = n - 2;
		return true;
	}
	for (int i = 3; i <= n / 2; i += 2)
		if (is_prime(n - i, are_primes) && is_prime(i, are_primes)) {
			*primes++ = i; *primes = n - i;
			return true;
		}
	return false;
}

bool sum_of_four_primes(int n, int* primes, const unsigned char* are_primes)
{
	if (n & 1) { // n is an odd number
		n -= 5;
		*primes = 2; *(primes + 1) = 3;
	}
	else {
		n -= 4;
		*primes = *(primes + 1) = 2;
	}
	return sum_of_two_primes(n, primes + 2, are_primes);
/*
	if (n & 1 || (n / 2) & 1) { // n or one-half of n is an odd number
		for (int i = 4; n - i > 4; i += 2)
			if (sum_of_two_primes(n - i, primes + 2, are_primes))
				return sum_of_two_primes(i, primes, are_primes);
		return false;
	}
	else {
		if (sum_of_two_primes(n / 2, primes, are_primes)) {
			*(primes + 2) = *primes; *(primes + 3) = *(primes + 1);
			return true;
		}
		else
			return false;
	}
*/
}

int main(int /* argc */, char** /* argv */)
{
	unsigned char* are_primes = generate_primes();
	// for non-negative integer i, primes[i / 8] & (1 << i % 8) is 1 if i is a prime, 0 otherwise
	int n;
	while (cin >> n) {
		const int nr_primes = 4;
		int primes[nr_primes];
		if (n > 7 && sum_of_four_primes(n, primes, are_primes)) {
			for (int i = 0; i < nr_primes; i++)
				cout << primes[i] << ((i == nr_primes - 1) ? '\n' : ' ');
		}
		else
			cout << "Impossible.\n";
	}
	delete[] are_primes;
	return 0;
}


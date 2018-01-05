
/*
	UVa 10140 - Prime Distance

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10140_Prime_Distance.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

/*
	The implementation of segmented sieve of Eratosthenes is originated from
		http://www.prefield.com/algorithm/math/segment_sieve.html, 
	since there are no explicit articles related to this subject found in the internet.
*/

const int sqrt_h_max = 49152 /* 46341 */; // should be greter than sqrt(2147483648)
long long primes[sqrt_h_max];

const int difference_max = 1000000;
long long segmented_primes[difference_max + 1];

void generete_sieve() // generate prime numbers up to sqrt_h_max
{
	for (long long i = 2; i < sqrt_h_max; i++)
		primes[i] = i;
	for (long long i = 2; i * i < sqrt_h_max; i++)
		if (primes[i]) {
			for (long long j = i * i; j < sqrt_h_max; j += i)
				primes[j] = 0;
		}
	remove(primes, primes + sqrt_h_max, 0);
}

void generate_segmented_sieve(long long l, long long h) // segmented sieve for [l, h)
{
	for (long long i = l; i < h; i++)
		segmented_primes[i - l] = i;
	for (long long i = 0; primes[i] * primes[i] < h; i++) {
		long long j;
	    if (primes[i] >= l)
			j = primes[i] * primes[i];
		else if (!(l % primes[i]))
			j = l;
		else
			j = l - (l % primes[i]) + primes[i];
		for ( ; j < h; j += primes[i])
			segmented_primes[j - l] = 0;
  }
}

long long get_next_prime(long long i, long long l, long long h)
{
	if (i > 2) {
		if (!(i & 1))
			i++;
	}
	else
		return (h > 2) ? 2 : -1;
	while (i < h && !segmented_primes[i - l])
		i += 2;
	return (i < h) ? i : -1;
}

int main()
{
	generete_sieve();
	long long l, u;
	while (cin >> l >> u) {
		u++;
		generate_segmented_sieve(l, u);
		long long min_distance = u - l, max_distance = 0;
		long long min_l, min_u, max_l, max_u;
		long long i = get_next_prime(l, l, u);
		if (i != -1) {
			while (i < u) {
				long long j = get_next_prime(i + 1, l, u);
				if (j == -1)
					break;
				if (j - i > max_distance) {
					max_distance = j - i;
					max_l = i; max_u = j;
				}
				if (j - i < min_distance) {
					min_distance = j - i;
					min_l = i; min_u = j;
				}
				i = j;
			}
		}
		if (max_distance)
			cout << min_l << ',' << min_u << " are closest, " << max_l << ',' << max_u << " are most distant.\n";
		else
			cout << "There are no adjacent primes.\n";
	}
	return 0;
}


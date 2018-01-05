
/*
	UVa 10539 - Almost Prime Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10539_Almost_Prime_Numbers.cpp
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const long long n_max = 1000000000000;
const int sqrt_n_max = 1000000;
bool not_primes[sqrt_n_max + 1]; // not_primes[i] is true if i is not a prime
const int nr_almost_primes_max = 100000;
long long almost_primes[nr_almost_primes_max];

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(sqrt_n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= sqrt_n_max; j += i)
				not_primes[j] = true;
		}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	int nr_almost_primes = 1;
	for (long long j = 4; j <= n_max; j <<= 1)
		almost_primes[nr_almost_primes++] = j;
	for (int i = 3; i <= sqrt_n_max; i += 2) {
		if (!not_primes[i]) {
			long long j = i;
			for (j *= j; j <= n_max; j *= i)
				almost_primes[nr_almost_primes++] = j;
		}
	}
#ifdef DEBUG
	cout << nr_almost_primes << endl;
#endif
	sort(almost_primes, almost_primes + nr_almost_primes);

	int N;
	cin >> N;
	while (N--) {
		long long low, high;
		cin >> low >> high;
		int li = distance(almost_primes, upper_bound(almost_primes, almost_primes + nr_almost_primes, low - 1));
		int hi = distance(almost_primes, upper_bound(almost_primes, almost_primes + nr_almost_primes, high));
		cout << hi - li << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}



/*
	UVa 11408 - Count DePrimes

	To build using Visual Studio 2012
		cl -EHsc -O2 UVa_11408_Count_DePrimes.cpp

	An accepted solution.
*/

#include <iostream>
using namespace std;

const int n_max = 5000000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int sums[n_max + 1]; // sums[i] is the sum of i's prime factors
int nr_deprimes[n_max + 1]; // nr_deprimes[i] is the number of DePrimes up to i

int main()
{
	sums[2] = 2;
	for (int i = 2 * 2; i <= n_max ; i += 2) {
		not_primes[i] = true;
		sums[i] = 2;
	}
	for(int i = 3; i <= n_max; i += 2)
		if(!not_primes[i]) {
			sums[i] = i;
			for(int j = i * 2; j <= n_max; j += i) {
				not_primes[j] = true;
				sums[j] += i;
			}
		}

	nr_deprimes[2] = 1;
	for(int i = 3; i <= n_max; i++) {
		nr_deprimes[i] = nr_deprimes[i - 1];
		if (!not_primes[sums[i]])
			nr_deprimes[i]++;
	}
#ifdef DEBUG
	cout << nr_deprimes[n_max] << endl;
#endif
	int a, b;
	while (true) {
		int a, b;
		cin >> a;
		if (!a)
			break;
		cin >> b;
		cout << nr_deprimes[b] - nr_deprimes[a - 1] << endl;
	}
	return 0;
}


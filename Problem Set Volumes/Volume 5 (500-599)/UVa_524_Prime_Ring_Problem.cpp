
/*
	UVa 524 - Prime Ring Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_524_Prime_Ring_Problem.cpp
*/

#include <iostream>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 16;
bool primes[n_max * 2 + 1]; // primes[i] is true if i is a prime
bool prime_pairs[n_max + 1][n_max + 1]; // prime_pairs[i][j] is true if sum of i and j is a prime
bool in_ring[n_max + 1]; // in_ring[i] is true if i has already been in a ring
int ring[n_max + 1]; // ring[i] is the i-th number in a ring

void prime_ring(int ri, int n)
{
	if (ri > n) {
		if (prime_pairs[ring[ri - 1]][1]) {
			cout << 1;
			for (int i = 2; i <= n; i++)
				cout << ' ' << ring[i];
			cout << endl;
		}
	}
	else {
		int pn = ring[ri - 1];
		for (int i = (ri & 1) ? 3 : 2; i <= n; i += 2)
			if (!in_ring[i] && prime_pairs[pn][i]) {
				in_ring[i] = true;
				ring[ri] = i;
				prime_ring(ri + 1, n);
				in_ring[i] = false;
			}
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	primes[2] = primes[3] = primes[5] = primes[7] = primes[11] =
		primes[13] = primes[17] = primes[19] = primes[23] = primes[29] = primes[31] = true;
	for (int i = 1; i < n_max; i++)
		for (int j = i + 1; j <= n_max; j++)
			if (primes[i + j])
				prime_pairs[i][j] = prime_pairs[j][i] = true;

	int c = 1, n;
	while (cin >> n) {
		if (c > 1)
			cout << endl;
		cout << "Case " << c++ <<":\n";
		memset(in_ring, 0, sizeof(in_ring));
		ring[1] = 1;
		prime_ring(2, n);
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


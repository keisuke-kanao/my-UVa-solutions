
/*
	UVa 914 - Jumping Champion

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_914_Jumping_Champion.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

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

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	int nr_primes = 0, nr_diffs = 0;
	for (int i = 2, pi = 0; i <= n_max; i++)
		if (!not_primes[i]) {
			if (nr_primes)
				nr_diffs = max(nr_diffs, i - pi);
			nr_primes++;
			pi = i;
		}
#ifdef DEBUG
	cout << nr_primes << ' ' << nr_diffs << endl;
#endif
	vector<int> primes(nr_primes);
	for (int i = 2, pi = 0; i <= n_max; i++)
		if (!not_primes[i])
			primes[pi++] = i;

	int t;
	cin >> t;
	while (t--) {
		int l, u;
		cin >> l >> u;
		bool no_jumping_champion = false;
		int diff = 0;
		if (u < primes[0] || l > primes[nr_primes - 1])
			no_jumping_champion = true; // no primes between l and u
		else {
			if (u > primes[nr_primes - 1])
				u = primes[nr_primes - 1];
			int li = distance(primes.begin(), lower_bound(primes.begin(), primes.end(), l)),
				ui = distance(primes.begin(), lower_bound(primes.begin(), primes.end(), u));
			if (primes[ui] != u)
				ui--;
			if (ui - li > 0) {
				vector<int> diffs(nr_diffs + 1, 0); // diffs[i] is the number of occurrences of difference i
				for (int i = li + 1; i <= ui; i++)
					diffs[primes[i] - primes[i - 1]]++;
				int max_occurences = 0;
				for (int i = 1; i <= nr_diffs; i++)
					max_occurences = max(max_occurences, diffs[i]);
				int nr_max_occurences = 0;
				for (int i = 1; i <= nr_diffs; i++)
					if (diffs[i] == max_occurences) {
						diff = i;
						if (++nr_max_occurences > 1)
							break;
					}
				if (nr_max_occurences > 1)
					no_jumping_champion = true;
			}
			else
				no_jumping_champion = true;
		}
		if (no_jumping_champion)
			cout << "No jumping champion\n";
		else
			cout << "The jumping champion is " << diff << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


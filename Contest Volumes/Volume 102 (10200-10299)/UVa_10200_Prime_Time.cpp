
/*
	UVa 10200 - Prime Time

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10200_Prime_Time.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 10000;
int nr_primes[n_max + 1]; // nr_primes[i] is the number of primes up to i

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 0, nr = 0; i <= n_max; i++) {
		if (is_prime(i * i + i + 41))
			nr++;
		nr_primes[i] = nr;
	}

	int a, b;
	while (cin >> a >> b) {
		int nr = nr_primes[b];
		if (a)
			nr -= nr_primes[a - 1];
		cout << fixed << setprecision(2) << static_cast<double>(nr) * 100 / static_cast<double>(b - a + 1) + 1.0e-8 << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


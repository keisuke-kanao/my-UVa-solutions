
/*
	UVa 686 - Goldbach's Conjecture (II)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_686_Goldbachs_Conjecture_II.cpp

	This problem is similar to 543 - Goldbach's Conjecture.
*/

#include <iostream>
#include <cstring>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 32768;
bool odd_primes[n_max / 2]; // odd_primes[i] is true if the odd number of (2 * i + 1) is a prime one

bool is_prime(int n)
{
/*
	if (n < 2)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
*/
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
/*
	}
*/
	return true;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	memset(odd_primes, 0, sizeof(odd_primes));
	for (int i = 1; i < n_max / 2; i++)
		if (is_prime(i * 2 + 1))
			odd_primes[i] = true;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int nr = 0;
		if (n == 4)
			nr = 1;
		else {
			int a = 3, b = n - 3;
			for ( ; a <= b; a += 2, b -= 2)
				if (odd_primes[a / 2] && odd_primes[b / 2])
					nr++;
		}
		cout << nr << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}



/*
	UVa 160 - Factors and Factorials

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_160_Factors_and_Factorials.cpp
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

const int n_max = 100;
bool primes[n_max + 1]; // primes[i] is true if i is a prime number
int nr_primes[n_max + 1]; // nr_primes[i] is the number of occurrences for the prime number of i

void prime_factorization(int n)
{
	for ( ; !(n & 1); n >>= 1)
		nr_primes[2]++;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			nr_primes[i]++;
			n /= i;
		}
		else
			i += 2;
	}
	if (n > 1)
		nr_primes[n]++;
}

int main()
{
	memset(primes, 0, sizeof(primes));
	primes[2] = primes[3] = primes[5] =primes[7] =primes[11] =primes[13] = primes[17] = primes[19] = primes[23] = primes[29] =
		primes[31] = primes[37] = primes[41] = primes[43] = primes[47] = primes[53] = primes[59] = primes[61] = primes[67] =
		primes[71] = primes[73] = primes[79] = primes[83] = primes[89] = primes[97] = true;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (n == 1) {
			cout << "  1! =  1\n";
			continue;
		}
		memset(nr_primes, 0, sizeof(nr_primes));
		for (int i = 2; i <= n; i++)
			prime_factorization(i);
		cout << setfill(' ') << setw(3) << n << "! =";
		int nr_printed = 0;
		for (int i = 2; i <= n; i++)
			if (primes[i]) {
				if (nr_printed && !(nr_printed % 15))
					cout << "      ";
				cout << setw(3) << nr_primes[i];
				nr_printed++;
				if (!(nr_printed % 15))
					cout << endl;
			}
		if (nr_printed % 15)
			cout << endl;
	}
	return 0;
}


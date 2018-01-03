
/*
	UVa 543 - Goldbach's Conjecture

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_543_Goldbachs_Conjecture.cpp

	from University of Ulm Local Contest 1998 Problem G
		(http://www.informatik.uni-ulm.de/acm/Locals/1998/)
*/

#include <iostream>
#include <cstring>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 1000000;
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
		int a = 3, b = n - 3;
		for ( ; a <= b; a += 2, b -= 2)
			if (odd_primes[a / 2] && odd_primes[b / 2])
				break;
		if (a <= b)
			cout << n << " = " << a << " + " << b << endl;
		else
			cout << "Goldbach's conjecture is wrong.\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


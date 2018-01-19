
/*
	7.6.4 Factovisors
	PC/UVa IDs: 110704/10139, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10139_Factovisors.cpp
*/

#include <iostream>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

bool is_prime(int n)
{
	if (n < 2)
		return false;
	else if (n == 2)
		return true;
	else if(!(n % 2))
		return false;
	else {
		for (int i = 3; i <= sqrt(static_cast<double>(n)) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	if (!y)
		return x;
	else
		return gcd(y, x % y);
}

bool is_factovisors(int n, int m) // see if m divides n!
{
	if (is_prime(m) && n < m)
		return false;
	while (true) {
		if (!m)
			return false;
		else if (m == 1)
			return true;
		else if (n <= 1)
			return false;
		else if (m <= n)
			return true;
		else {
			int d = gcd(n, m);
			n--; 
			if (d > 1) {
				m /= d;
				if (n < m && is_prime(m))
					return false;
			}
		}
	}
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n, m;
	while (cin >> n >> m) {
		cout << m << ((is_factovisors(n, m)) ? " divides " : " does not divide ") << n << "!\n"; 
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}


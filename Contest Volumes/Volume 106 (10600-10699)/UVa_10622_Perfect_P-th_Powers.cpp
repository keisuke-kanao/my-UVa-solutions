
/*
	UVa 10622 - Perfect P-th Powers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10622_Perfect_P-th_Powers.cpp

	from Waterloo local contest - 31 January, 2004 Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/040131/data/)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

size_t prime_factorization(long long n, vector<int>& powers)
{
	if (n == 1) {
		powers.push_back(1);
		return 1;
	}
	bool a_new_prime = true;
	for ( ; !(n & 1); n >>= 1) {
		if (a_new_prime) {
			a_new_prime = false;
			powers.push_back(1);
		}
		else
			powers.back()++;
	}
	a_new_prime = true;
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			if (a_new_prime) {
				a_new_prime = false;
				powers.push_back(1);
			}
			else
				powers.back()++;
			n /= i;
		}
		else {
			i += 2;
			a_new_prime = true;
		}
	}
	if (n > 1)
		powers.push_back(1);
	return powers.size();
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	while (true) {
		long long x;
		cin >> x;
		if (!x)
			break;
		vector<int> powers;
		size_t nr_powers = prime_factorization(((x < 0) ? -x : x), powers);
#ifdef DEBUG
		for (size_t i = 0; i < nr_powers; i++) {
			if (i)
				cout << ' ';
			cout << powers[i];
		}
		cout << endl;
#endif
		int min_power = powers[0];
		for (size_t i = 0; i < nr_powers - 1; i++)
			for (size_t j = i; j < nr_powers; j++)
				min_power = min(min_power, gcd(powers[i], powers[j]));
		if (x < 0) {
			while (!(min_power & 1))
				min_power >>= 1;
		}
		cout << min_power << endl;
	}
	return 0;
}


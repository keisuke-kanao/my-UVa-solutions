
/*
	UVa 10879 - Code Refactoring

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10879_Code_Refactoring.2.cpp
*/

#include <iostream>
#include <map>
#include <set>
#include <cmath>
using namespace std;

void prime_factorization(int n, map<int, int>& primes)
{
	pair<map<int, int>::iterator, bool> result;
	result.first = primes.end();
	for ( ; !(n & 1); n >>= 1) {
		if (result.first == primes.end())
			result = primes.insert(make_pair(2, 1));
		else
			result.first->second++;
	}
	result.first = primes.end();
	int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n)) + 1);
	while (i <= e) {
		if (!(n % i)) {
			if (result.first == primes.end())
				result = primes.insert(make_pair(i, 1));
			else
				result.first->second++;
			n /= i;
			e = static_cast<int>(sqrt(static_cast<double>(n)) + 1);
		}
		else {
			result.first = primes.end();
			i += 2;
		}
	}
	if (n > 1) {
		result = primes.insert(make_pair(n, 1));
		if (!result.second)
			result.first->second++;
	}
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 1; c <= nr_cases; c++) {
		int k;
		cin >> k;
		map<int, int> primes; // key is a prime number, value is its number of occurrences
		prime_factorization(k, primes);
		set<int> factors;
		for (map<int, int>::const_iterator pi = primes.begin(), pe = primes.end(); pi != pe; ++pi) {
			if (factors.empty()) {
				for (int i = 0, p = 1; i < pi->second + 1; i++, p *= pi->first)
					factors.insert(p);
			}
			else {
				for (int i = 0, p = pi->first; i < pi->second; i++) {
					set<int> fs;
					for (set<int>::const_iterator fi = factors.begin(), fe = factors.end(); fi != fe; ++fi)
						fs.insert(p * (*fi));
					factors.insert(fs.begin(), fs.end());
				}
			}
		}
		set<int>::const_iterator fi = factors.begin();
		++fi;
		int i = *fi;
		++fi;
		int j = *fi;
		cout << "Case #" << c << ": " << k << " = " <<
				i << " * " << k / i << " = " << j << " * " << k / j << endl;
	}
	return 0;
}



/*
	UVa 10892 - LCM Cardinality

	To build using Visucal Studio 2010:
		cl -EHsc UVa_10892_LCM_Cardinality.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

size_t get_divisors(int n, vector<int>& divisors)
{
	for (int i = 1, e = static_cast<int>(sqrt(static_cast<double>(n))) + 1; i < e; i++)
		if (!(n % i)) {
			divisors.push_back(i);
			if (i != n / i)
				divisors.push_back(n / i);
		}
	return divisors.size();
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

long long lcm(int x, int y)
{
	long long l = x;
	return (l / gcd(x, y)) * y;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<int> divisors;
		size_t d = get_divisors(n, divisors);
		sort(divisors.begin(), divisors.end());
		int c = 1; // for (n, n)
		for (size_t i = 0; i < d - 1; i++)
			for (size_t j = i + 1; j < d; j++)
				if (lcm(divisors[i], divisors[j]) == n) {
					c++;
#ifdef DEBUG
					cout << divisors[i] << ' ' <<  divisors[j] << endl;
#endif
				}
		cout << n << ' ' << c << endl;
	}
	return 0;
}


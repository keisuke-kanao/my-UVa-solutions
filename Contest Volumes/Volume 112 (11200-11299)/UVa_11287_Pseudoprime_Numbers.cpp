
/*
	UVa 11287 - Pseudoprime Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11287_Pseudoprime_Numbers.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

long long bigmod(long long b, long long p, long long m) // b^p mod m
{
	if (!p)
		return 1;
	else if (!(p & 1)) {
		long long bgm = bigmod(b, p / 2, m);
		return (bgm * bgm) % m;
	}
	else
		return ((b % m) * bigmod(b, p - 1, m)) % m;
}

int main()
{
	while (true) {
		int p, a;
		cin >> p >> a;
		if (!p && !a)
			break;
		bool seudoprime = !is_prime(p) && bigmod(a, p, p) == a;
		cout << ((seudoprime) ? "yes\n" : "no\n");
	}
	return 0;
}


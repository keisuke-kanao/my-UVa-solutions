
/*
	UVa 11609 - Teams

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11609_Teams.cpp
*/

/*
‡”k * C(n, k) (k = 0 ... n) = n * 2^(n - 1)

See Binomial coefficient From Wikipedia, the free encyclopedia (http://en.wikipedia.org/wiki/Binomial_coefficient).

*/

#include <iostream>
using namespace std;

long long bigmod(long long b, long long p, long long m)
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
	const long long m = 1000000007;
	int t;
	cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		long long n;
		cin >> n;
		cout << "Case #" << cn << ": " << ((n % m) * bigmod(2, n - 1, m)) % m << endl;
	}
	return 0;
}


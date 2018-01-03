
/*
	UVa 1230 - MODEX

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1230_MODEX.cpp

	This problem is similar to UVa 374 - Big Mod.
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
	int c;
	cin >> c;
	while (c--) {
		long long x, y, n;
		cin >> x >> y >> n;
		cout << bigmod(x, y, n) << endl;
	}
	cin >> c;
	return 0;
}


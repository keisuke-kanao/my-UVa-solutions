
/*
	UVa 374 - Big Mod

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_374_Big_Mod.cpp
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
	long long b, p, m;
	while (cin >> b >> p >> m)
		cout << bigmod(b, p, m) << endl;
	return 0;
}


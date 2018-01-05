
/*
	UVa 10493 - Cats, with or without Hats

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10493_Cats_with_or_without_Hats.cpp
*/

#include <iostream>
using namespace std;

int how_many_cats(int n, int m)
{
	if (n == 1)
		return (m == 1) ? -1 : 0;
	if (m == 1)
		return 1;
	int nc = m;
	while (m > 1) {
		if (m < n)
			return 0;
		nc += m / n;
		m = m / n + m % n;
	}
	return nc;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n)
			break;
		cout << n << ' ' << m << ' ';
		int nc = how_many_cats(n, m);
		if (nc == -1)
			cout << "Multiple\n";
		else if (!nc)
			cout << "Impossible\n";
		else
			cout << nc << endl;
	}
	return 0;
}


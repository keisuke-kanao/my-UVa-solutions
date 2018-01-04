
/*
	UVa 11417 - GCD

	To build using Visual Studio 2008:
		cl -EHsc -O2 -DONLINE_JUDGE UVa_11417_GCD.cpp
*/

#include <iostream>
using namespace std;

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

#ifdef ONLINE_JUDGE

int main()
{
	const int n_max = 500;
	int gs[n_max + 1];
	gs[1] = 0;
	for (int i = 2; i <= n_max; i++) {
		int g = 0;
		for (int j = 1; j < i; j++)
			g += gcd(j, i);
		gs[i] = gs[i - 1] + g;
	}
#ifdef DEBUG
	cout << gs[n_max] << endl;
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << gs[n] << endl;
	}
	return 0;
}

#else

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int g = 0;
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				g += gcd(i, j);
		cout << g << endl;
	}
	return 0;
}

#endif


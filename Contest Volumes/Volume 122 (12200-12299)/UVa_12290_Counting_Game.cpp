
/*
	UVa 12290 - Counting Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12290_Counting_Game.cpp
*/

#include <cstdio>

bool contain_digit_7(int n)
{
	do {
		if (n % 10 == 7)
			return true;
		n /= 10;
	} while (n);
	return false;
}

int main()
{
	while (true) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		if (!n && !m && !k)
			break;
		int i = m;
		bool inc = false;
		while (true) {
			if (!(i % 7) || contain_digit_7(i)) {
				if (!--k)
					break;
			}
			if (m == 1 || m == n)
				i += 2 * (n - 1);
			else {
				i += (inc) ? 2 * (m - 1) : 2 * (n - m);
				inc = !inc;
			}
		}
		printf("%d\n", i);
	}
	return 0;
}


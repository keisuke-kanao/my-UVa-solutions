
/*
	UVa 10193 - All You Need Is Love

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10193_All_You_Need_Is_Love.cpp
*/

#include <cstdio>
#include <cstdlib>

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int tc = 1; tc <= n; tc++) {
		const int nr_chars_max = 30;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int n1 = static_cast<int>(strtol(s, NULL, 2));
		scanf("%s", s);
		int n2 = static_cast<int>(strtol(s, NULL, 2));
		printf("Pair #%d", tc);
		if (gcd(n1, n2) > 1)
			printf(": All you need is love!\n");
		else
			printf(": Love is not all you need!\n");
	}
	return 0;
}


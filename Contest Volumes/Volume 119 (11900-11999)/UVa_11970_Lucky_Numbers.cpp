
/*
	UVa 11970 - Lucky Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11970_Lucky_Numbers.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		int n;
		scanf("%d", &n);
		printf("Case %d:", cn);
		// 0 < sqrt(N - X) < sqrt(N)
		for (int i = static_cast<int>(sqrt(static_cast<double>(n))); i; i--) {
			int x = n - i * i;
			if (x && !(x % i))
				printf(" %d", x);
		}
		putchar('\n');
	}
	return 0;
}


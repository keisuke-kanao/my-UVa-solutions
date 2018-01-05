
/*
	UVa 11247 - Income Tax

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11247_Income_Tax.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		long long m;
		int x;
		scanf("%lld %d", &m, &x);
		if (!m && !x)
			break;
		// v * (100 - x) / 100 < m - 1 or v < 100 * (m - 1) / (100 - x)
		if (m == 1 || x == 0 || x == 100)
			puts("Not found");
		else {
			long long v = 100 * (m - 1) / (100 - x);
			if (v * (100 - x) == (m - 1) * 100)
				v--;
			if (v < m)
				puts("Not found");
			else
				printf("%lld\n", v);
		}
	}
	return 0;
}


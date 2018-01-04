
/*
	UVa 12459 - Bees' ancestors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12459_Bees_ancestors.cpp
*/

#include <cstdio>

int main()
{
	const int n_max = 80;
	long long males[n_max + 1], females[n_max + 1];
	males[0] = 1; females[0] = 0;
	for (int i = 1; i <= n_max; i++) {
		males[i] = females[i - 1];
		females[i] = males[i - 1] + females[i - 1];
#ifdef DEBUG
		printf("%lld %lld\n", males[i], females[i]);
#endif
	}
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		printf("%lld\n", males[n] + females[n]);
	}
	return 0;
}


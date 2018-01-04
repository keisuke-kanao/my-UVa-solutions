
/*
	UVa 12708 - GCD The Largest

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12708_GCD_The_Largest.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		long long N;
		scanf("%lld", &N);
		printf("%lld\n", N / 2);
	}
	return 0;
}



/*
	UVa 11986 - Save from Radiation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11986_Save_from_Radiation.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		long long N;
		scanf("%lld", &N);
		int nr = 0;
		for ( ; N; N >>= 1)
			nr++;
		printf("Case %d: %d\n", t, nr);
	}
	return 0;
}


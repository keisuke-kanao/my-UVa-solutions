
/*
	UVa 13059 - Tennis Championship

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_13059_Tennis_Championship.cpp
*/

#include <cstdio>

int main()
{
	long long P;
	while (scanf("%lld", &P) != EOF) {
		long long nr_matches = 0;
		while (P > 1) {
			long long p = P >> 1;
			nr_matches += p;
			if (P & 1)
				p++;
			P = p;
		}
		printf("%lld\n", nr_matches);
	}
	return 0;
}



/*
	UVa 11270 - Tiling Dominoes

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11270_Tiling_Dominoes.cpp
*/

/*
About the formula to calculate the number of tilings, see http://en.wikipedia.org/wiki/Domino_tiling.
*/

#include <cstdio>
#include <cmath>

int main()
{
	const double pi = 2.0 * acos(0.0);

	int m, n;
	while (scanf("%d %d", &m, &n) != EOF) {
		double nr_tilings = 1.0;
		for (int j = 1; j <= (m + 1) / 2; j++) {
			double d = cos(pi * j / (m + 1));
			for (int k = 1; k <= (n + 1) / 2; k++) {
				double e = cos(pi * k / (n + 1));
				nr_tilings *= 4.0 * (d * d + e * e);
			}
		}
		printf("%.0f\n", nr_tilings);
	}
	return 0;
}


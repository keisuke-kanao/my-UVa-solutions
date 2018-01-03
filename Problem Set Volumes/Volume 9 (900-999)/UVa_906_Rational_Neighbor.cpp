
/*
	UVa 906 - Rational Neighbor

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_906_Rational_Neighbor.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	long long a, b;
	while (scanf("%lld %lld", &a, &b) != EOF) {
		double n;
		scanf("%lf", &n);
		long long m = static_cast<long long>(ceil(1.0 / (n * b)));
		long long c, d;
		bool done = false;
		for (d = m; ; d++) {
			for (c = static_cast<long long>(static_cast<double>(a) * d / b); ; c++) {
				long long e = b * c - a * d;
				if (e <= 0)
					continue;
				if (e <= n * b * d) {
					done = true;
					break;
				}
				else
					break;
			}
			if (done)
				break;
		}
		printf("%lld %lld\n", c, d);
	}
	return 0;
}



/*
	UVa 11646 - Athletics Track

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11646_Athletics_Track.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	const double pi = 2.0 * acos(0.0);
	double a, b;
	for (int cn = 1; scanf("%lf : %lf", &a, &b) != EOF; cn++) {
		double angle = pi - 2.0 * atan2(a, b);
		double l = 400.0 / (2.0 + angle * sqrt((a * a + b * b) / (a * a))), w = l * b / a;
		printf("Case %d: %.10lf %.10lf\n", cn, l, w);
	}
	return 0;
}


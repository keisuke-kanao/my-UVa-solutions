
/*
	UVa 10466 - How Far?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10466_How_Far.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	const double pi = 2.0 * acos(0.0);
	int n;
	double T;
	while (scanf("%d %lf", &n, &T) != EOF) {
		double angle, x = 0.0, y = 0.0, r, t;
		while (n--) {
			scanf("%lf %lf", &r, &t);
			angle = T * pi * 2.0 / t;
			x += r * cos(angle), y += r * sin(angle);
			printf("%.4lf%c", sqrt(x * x + y * y), ((n) ?  ' ' : '\n'));
		}
	}
	return 0;
}


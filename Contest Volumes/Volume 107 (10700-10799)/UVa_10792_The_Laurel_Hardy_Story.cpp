
/*
	UVa 10792 - The Laurel-Hardy Story

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10792_The_Laurel_Hardy_Story.cpp
*/

#include <cstdio>
#include <cmath>

double square(double d)
{
	return d * d;
}

int main()
{
	const double pi = 2.0 * acos(0.0);
	int N;
	scanf("%d", &N);
	for (int n = 1; n <= N; n++) {
		double r, d, h1;
		scanf("%lf %lf %lf", &r, &d, &h1);
		double a = asin((r - h1) / r), b = asin((r - d) / r);
		printf("Case %d: %.4lf\n", n, h1 +  2.0 * sqrt(square(r) - square(r - d)) * sin(a - b));
	}
	return 0;
}



/*
	UVa 11130 - Billiard bounces

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11130_Billiard_bounces.cpp
*/

#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	while (true) {
		double a, b, v, A, s;
		scanf("%lf %lf %lf %lf %lf", &a, &b, &v, &A, &s);
		if (!a)
			break;
		int hw = static_cast<int>((b + v * s * sin((A * pi) / 180.0)) / (2 * b)),
			vw = static_cast<int>((a + v * s * cos((A * pi) / 180.0)) / (2 * a));
		printf("%d %d\n", vw, hw);
	}
	return 0;
}


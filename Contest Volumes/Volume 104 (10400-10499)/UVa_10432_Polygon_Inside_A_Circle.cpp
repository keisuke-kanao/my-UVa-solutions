
/*
	UVa 10432 - Polygon Inside A Circle

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10432_Polygon_Inside_A_Circle.cpp
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	double r, n;
	while (cin >> r >> n)
		printf("%.3lf\n", r * r * n * sin(pi / n) * cos(pi / n));
	return 0;
}


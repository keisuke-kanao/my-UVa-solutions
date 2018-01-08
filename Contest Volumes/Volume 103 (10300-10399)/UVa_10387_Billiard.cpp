
/*
	UVa 10387 - Billiard

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10387_Billiard.cpp

	from Waterloo Local Contest Jun. 19, 1999 Problem A
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double pi = 2.0 * acos(0.0);

int main()
{
	while (true) {
		double a, b, s, m, n;
		cin >> a >> b >> s >> m >> n;
		if (a == 0.0 && b == 0.0 && s == 0.0 && m == 0.0 && n == 0.0)
			break;
		double x = a * m, y = b * n;
		double angle = atan2(y, x) * 180.0 / pi;
		double velocity = sqrt(x * x + y * y) / s;
		printf("%.2lf %.2lf\n", angle, velocity);
	}
	return 0;
}


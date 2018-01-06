
/*
	UVa 10060 - A hole to catch a man

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10060_A_hole_to_catch_a_man.cpp
*/

#include <cstdio>
#include <cmath>

const double pi = 2.0 * acos(0.0);

double get_sheet_volume()
{
	double T, x0, y0;
	scanf("%lf %lf %lf", &T, &x0, &y0);
	double x = x0, y = y0, area = 0.0;
	while (true) {
		double nx, ny;
		scanf("%lf %lf", &nx, &ny);
		area += x * ny - nx * y;
		x = nx, y = ny;
		if (x == x0 && y == y0)
			break;
	}
	return T * fabs(area) / 2.0;
}

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		double sv = 0.0;
		while (N--)
			sv += get_sheet_volume();
		double R, T;
		scanf("%lf %lf", &R, &T);
		double cv = pi * R * R * T;
		printf("%d\n", static_cast<int>(sv / cv));
	}
	return 0;
}


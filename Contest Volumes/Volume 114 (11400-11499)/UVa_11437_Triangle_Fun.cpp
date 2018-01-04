
/*
	UVa 11437 - Triangle Fun

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11437_Triangle_Fun.cpp
*/

#include <cstdio>
#include <cmath>

struct point {
	double x, y;
};

double signed_triangle_area(const point& a, const point& b, const point& c)
{
	return (a.x * b.y - a.y * b.x + a.y * c.x - a.x * c.y + b.x * c.y - c.x * b.y) / 2.0;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		point a, b, c;
		scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
		// from Menelaus' theorem, PQR = ABC / 7
		printf("%.0lf\n", fabs(signed_triangle_area(a, b, c)) / 7.0);
	}
	return 0;
}


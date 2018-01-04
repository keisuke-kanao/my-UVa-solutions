
/*
	UVa 190 - Circle Through Three Points

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_190_Circle_Through_Three_Points.cpp
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double euclidean_distance(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2, dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

double calculate_r(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double a = euclidean_distance(x1, y1, x2, y2), b = euclidean_distance(x2, y2, x3, y3),
		c = euclidean_distance(x3, y3, x1, y1);
	return (a * b * c) / sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c));
}

void calculate_h_k(double x1, double y1, double x2, double y2, double x3, double y3, double& h, double& k)
{
	double a1 = 2.0 * (x2 - x1);
	double b1 = 2.0 * (y2 - y1);
	double c1 = x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2;
	double a2 = 2.0 * (x3 - x1);
	double b2 = 2.0 * (y3 - y1);
	double c2 = x1 * x1 -x3 * x3 + y1 * y1 - y3 * y3;
	h = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
	k = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);
}

int main()
{
	double x1, y1, x2, y2, x3, y3;
	while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
		double r = calculate_r(x1, y1, x2, y2, x3, y3);
		double h, k;
		calculate_h_k(x1, y1, x2, y2, x3, y3, h, k);
		double c = -2.0 * h, d = -2.0 * k, e = h * h + k * k - r * r;
		printf("(x %c %.3lf)^2 + (y %c %.3lf)^2 = %.3lf^2\n",
			((h < 0.0) ? '+' : '-'), fabs(h), ((k < 0.0) ? '+' : '-'), fabs(k), r);
		printf("x^2 + y^2 %c %.3lfx %c %.3lfy %c %.3lf = 0\n\n",
			((c < 0.0) ? '-' : '+'), fabs(c), ((d < 0.0) ? '-' : '+'), fabs(d), ((e < 0.0) ? '-' : '+'), fabs(e));
	}
	return 0;
}


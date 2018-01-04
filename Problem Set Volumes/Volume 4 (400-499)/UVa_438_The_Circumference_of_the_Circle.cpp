
/*
	UVa 438 - The Circumference of the Circle

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_438_The_Circumference_of_the_Circle.cpp

	from University of Ulm Local Contest 1996 Problem C
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

/*
	Let R be he diameter of the circumcircle, then:
		R = (2 * a * b * c) / sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c))
	where a, b, c are the lengths of the sides of the triangle.
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double pi = 2.0 * acos(0.0);

double euclidean_distance(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2, dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	double x1, y1, x2, y2, x3, y3;
	while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
		double a = euclidean_distance(x1, y1, x2, y2), b = euclidean_distance(x2, y2, x3, y3),
			c = euclidean_distance(x3, y3, x1, y1);
		double r = (2.0 * a * b * c) / sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c));
		printf("%.2lf\n", pi * r);
	}
	return 0;
}



/*
	UVa 11068 - An Easy Task

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11068_An_Easy_Task.cpp
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

#define EPSILON numeric_limits<float>::epsilon()

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;}
};

struct line { // a * x + b * y + c = 0
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term

	line(double _a, double _b, double _c);
};

line::line(double _a, double _b, double _c)
	: a(_a), b(_b), c(_c)
{
	if (b) {
		a /= b; c /= b; b = 1.0;
	}
	else if (a) {
		b /= a; c /= a; a = 1.0;
	}
}

bool parallelQ(const line& l1, const line& l2)
{
	return fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON;
}

bool same_lineQ(const line& l1, const line& l2)
{
	return parallelQ(l1, l2) && fabs(l1.c - l2.c) <= EPSILON;
}

bool intersection_point(const line& l1, const line& l2, point& p)
{
	if (same_lineQ(l1, l2))
		return false;

	if (parallelQ(l1, l2))
		return false;

	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

	if (fabs(l1.b) > EPSILON) // test for vertical line
		p.y = - (l1.a * p.x + l1.c) / l1.b;
	else
		p.y = - (l2.a * p.x + l2.c) / l2.b;
	if (fabs(p.x) > numeric_limits<float>::max() || fabs(p.y) > numeric_limits<float>::max())
		return false;
	if (fabs(p.x) < numeric_limits<float>::min())
		p.x = 0.0;
	if (fabs(p.y) < numeric_limits<float>::min())
		p.y = 0.0;
	return true;
}

int main()
{
	while (true) {
		int a1, b1, c1, a2, b2, c2;
		cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
		if (!a1 && !b1 && !c1 && !a2 && !b2 && !c2)
			break;
		line l1(a1, b1, -c1), l2(a2, b2, -c2);
		point p;
		if (intersection_point(l1, l2, p))
			cout << "The fixed point is at " <<
				fixed << setprecision(2) << p.x << ' ' << setprecision(2) << p.y << ".\n";
		else
			cout << "No fixed point exists.\n";
	}
	return 0;
}


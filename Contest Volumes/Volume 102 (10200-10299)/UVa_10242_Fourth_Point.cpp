
/*
	UVa 10242 - Fourth Point !!

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10242_Fourth_Point.cpp
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

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (fabs(p1.x - p2.x) <= EPSILON) {
		l.a = 1; l.b = 0; l.c = -p1.x;
	}
	else {
		l.b = 1;
		l.a = -(p1.y - p2.y)/(p1.x - p2.x);
		l.c = -(l.a * p1.x) - l.b * p1.y;
	}
}

void point_and_slope_to_line(point& p, double m, line& l)
{
	l.a = -m;
	l.b = 1;
	l.c = -(l.a * p.x) - l.b * p.y;
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
	if (same_lineQ(l1, l2)) {
#ifdef DEBUG
		printf("Warning: Identical lines, all points intersect.\n");
#endif
		return false;
	}

	if (parallelQ(l1, l2)) {
#ifdef DEBUG
		printf("Error: Distinct parallel lines do not intersect.\n");
#endif
		return false;
	}

	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

	if (fabs(l1.b) > EPSILON) // test for vertical line
		p.y = - (l1.a * p.x + l1.c) / l1.b;
	else
		p.y = - (l2.a * p.x + l2.c) / l2.b;
	return true;
}

int main()
{
	point p1, p2, p3, p4;
	while (cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y) {
		// p2 should be the common point
		if (p1 == p3) {
			p1 = p2; p2 = p3; p3 = p4;
		}
		else if (p1 == p4) {
			p1 = p2; p2 = p4;
		}
		else if (p2 == p3)
			p3 = p4;
		if (p1.x == p2.x) {
			p4.x = p3.x; p4.y = p1.y;
		}
		else {
			line l, l1, l2;
			points_to_line(p1, p2, l);
			point_and_slope_to_line(p3, -l.a / l.b, l1);
			points_to_line(p2, p3, l);
			point_and_slope_to_line(p1, -l.a / l.b, l2);
			intersection_point(l1, l2, p4);
		}
		cout << fixed << setprecision(3) << p4.x << ' ' << p4.y << endl;
	}
	return 0;
}


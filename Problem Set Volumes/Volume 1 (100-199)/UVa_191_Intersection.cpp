
/*
	UVa 191 - Intersection

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_191_Intersection.cpp

	from ACM Southwestern European Regional Contest 1995 Problem A
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1995/index.html)
*/

#include <iostream>
#include <algorithm>
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

struct line_segment {
	point p1, p2;
	line_segment(const point& _p1, const point& _p2) : p1(_p1), p2(_p2) {}
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

bool parallelQ(const line& l1, const line& l2)
{
	return fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON;
}

bool same_lineQ(const line& l1, const line& l2)
{
	return parallelQ(l1, l2) && fabs(l1.c - l2.c) <= EPSILON;
}

bool point_in_box(const point& p, const point& b1, const point& b2)
{
	return p.x >= min(b1.x, b2.x) - EPSILON && p.x <= max(b1.x, b2.x) + EPSILON &&
		p.y >= min(b1.y, b2.y)- EPSILON && p.y <= max(b1.y, b2.y) + EPSILON;
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

bool line_segments_intersect(const line_segment& s1, const line_segment& s2, point& p)
{
	line l1, l2;
	points_to_line(s1.p1, s1.p2, l1);
	points_to_line(s2.p1, s2.p2, l2);
	if (same_lineQ(l1, l2)) // overlapping or disjoint segments
		return point_in_box(s1.p1, s2.p1, s2.p2) || point_in_box(s1.p2, s2.p1, s2.p2);
	if (parallelQ(l1, l2))
		return false;
	intersection_point(l1, l2, p);
	return point_in_box(p, s1.p1, s1.p2) && point_in_box(p, s2.p1, s2.p2);
}

bool is_intersect(const line_segment& ls, const point& p1, const point& p2)
{
	line_segment ls2(p1, p2);
	point p;
	return line_segments_intersect(ls, ls2, p);
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		point lp1, lp2;
		double left, top, right, bottom;
		cin >> lp1.x >> lp1.y >> lp2.x >>lp2.y >> left >> top >> right >> bottom;
		if (left > right)
			swap(left, right);
		if (top < bottom)
			swap(top, bottom);
		bool result = point_in_box(lp1, point(left, bottom), point(right, top)) ||
			point_in_box(lp2, point(left, bottom), point(right, top));
		if (!result) {
			line_segment ls(lp1, lp2);
			result = is_intersect(ls, point(left, bottom), point(left, top)) ||
				is_intersect(ls, point(left, top), point(right, top)) ||
				is_intersect(ls, point(right, top), point(right, bottom)) ||
				is_intersect(ls, point(right, bottom), point(left, bottom));
		}
		cout << ((result) ? "T\n" : "F\n");
	}
	return 0;
}

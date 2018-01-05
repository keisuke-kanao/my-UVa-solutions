
/*
	UVa 10263 - Railway

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10263_Railway.cpp
*/

#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

#define EPSILON numeric_limits<float>::epsilon()

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	point& operator=(const point& p) {x = p.x; y = p.y; return *this;}
	bool operator==(const point& p) const {return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;}
};

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (p1.x == p2.x) {
		l.a = 1; l.b = 0; l.c = -p1.x;
	}
	else {
		l.b = 1;
		l.a = -(p1.y - p2.y) / (p1.x - p2.x);
		l.c = -(l.a * p1.x) - l.b * p1.y;
	}
}

void point_and_slope_to_line(const point& p, double m, line& l)
{
	l.a = -m;
	l.b = 1;
	l.c = -(l.a * p.x + l.b * p.y);
}

inline bool parallelQ(const line& l1, const line& l2)
{
	return fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON;
}

inline bool same_lineQ(const line& l1, const line& l2)
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

bool in_range(double d, double a, double b)
{
	return d >= min(a, b) - EPSILON && d <= max(a, b) + EPSILON;
}

bool point_in_box(const point& p, const point& b1, const point& b2)
{
	return in_range(p.x, b1.x, b2.x) && in_range(p.y, b1.y, b2.y);
}

bool closest_point_from_line_segment(const point& p, const point& sp1, const point& sp2, point& closest_p)
{
	// get a line segment that connects sp1 and sp2
	line l;
	points_to_line(sp1, sp2, l);
	if (fabs(l.b) <= EPSILON) {	// vertical line
		if (in_range(p.y, sp1.y, sp2.y)) {
			closest_p.x = -l.c; closest_p.y = p.y;
			return true;
		}
		else
			return false;
	}
	if (fabs(l.a) <= EPSILON) {	// horizontal line
		if (in_range(p.x, sp1.x, sp2.x)) {
			closest_p.x = p.x; closest_p.y = -l.c;
			return true;
		}
		else
			return false;
	}
	line perp; // perpendicular to l through p
	point_and_slope_to_line(p, 1.0 / l.a, perp); // non-degenerate line
	intersection_point(l, perp, closest_p);
	return point_in_box(closest_p, sp1, sp2);
}

int main()
{
	point m;
	while (scanf("%lf %lf", &m.x, &m.y) != EOF) {
		int n;
		scanf("%d", &n);
		vector<point> points(n + 1);
		for (int i = 0; i <= n; i++)
			scanf("%lf %lf", &points[i].x, &points[i].y);
		double min_distance = numeric_limits<double>::max();
		point closest_p;
		for (int i = 0; i < n; i++) {
			// get the closest point on the line segment from m
			double d;
			point p;
			if (closest_point_from_line_segment(m, points[i], points[i + 1], p))
				d = euclidean_distance(p, m);
			else {
				double d1 = euclidean_distance(points[i], m), d2 = euclidean_distance(points[i + 1], m);
				if (d1 < d2) {
					d = d1; p = points[i];
				}
				else {
					d = d2; p = points[i + 1];
				}
			}
			if (d < min_distance) {
				min_distance = d;
				closest_p = p;
			}
		}
		printf("%.4lf\n%.4lf\n", closest_p.x, closest_p.y);
	}
	return 0;
}


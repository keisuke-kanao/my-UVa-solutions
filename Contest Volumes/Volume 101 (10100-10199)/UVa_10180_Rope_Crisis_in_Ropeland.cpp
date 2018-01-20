
/*
	13.6.2 Rope Crisis in Ropeland!
	PC/UVa IDs: 111302/10180, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10180_Rope_Crisis_in_Ropeland.cpp
*/

/*
	get a line that connects the two points
	calculate the closest point on the line from the center of the circle (the origin)
	if the distance between the closest point and the center of the circle is equal to or greater than 
	the radius of the circle, the minimum length of rope is the distance between the two points.
	else, the minimum length of rope is tangent lines from the both points plus the arc between them.
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

const double pi = 3.14159265358979323846;

struct point {
	double x, y;
};

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

struct circle {
	point c; // center of circle
	double r; // radius of circle
};

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
	return fabs(l1.a - l2.a) <= DBL_EPSILON && fabs(l1.b - l2.b) <= DBL_EPSILON;
}

inline bool same_lineQ(const line& l1, const line& l2)
{
	return parallelQ(l1, l2) && fabs(l1.c - l2.c) <= DBL_EPSILON;
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

	if (fabs(l1.b) > DBL_EPSILON) // test for vertical line
		p.y = - (l1.a * p.x + l1.c) / l1.b;
	else
		p.y = - (l2.a * p.x + l2.c) / l2.b;
	return true;
}

bool closest_point(const point& p_in, const line& l, point& p_c)
{
	if (fabs(l.b) <= DBL_EPSILON) {	// vertical line
		p_c.x = -(l.c);
		p_c.y = p_in.y;
		return true;
	}
	if (fabs(l.a) <= DBL_EPSILON) {	// horizontal line
		p_c.x = p_in.x;
		p_c.y = -(l.c);
		return true;
	}
	line perp; // perpendicular to l through (x, y)
	point_and_slope_to_line(p_in, 1/l.a, perp); // non-degenerate line
	return intersection_point(l, perp, p_c);
}

bool point_in_box(const point& p, const point& b1, const point& b2)
{
	return p.x >= min(b1.x, b2.x) && p.x <= max(b1.x, b2.x) && p.y >= min(b1.y, b2.y) && p.y <= max(b1.y, b2.y);
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

pair<double, double> tangent_line(const point& p, const circle& c)
{
	// calculate the length of a tangent line to the circle and its opposing angle
	pair<double, double> tangent;
	double d = euclidean_distance(c.c, p);
	tangent.first = sqrt(d * d - c.r * c.r); // tangent line length
	tangent.second = asin(tangent.first / d); // opposing angle of tangent line
	return tangent;
}

double normalize_angle(double a)
{
	if (a < -pi)
		a += pi * 2.0;
	else if (a > pi)
		a -= pi * 2.0;
	return a;
}

pair<double, double> angles_of_lines_perpendicular_to_tangent_line(const point& p, double ta)
{
	double a = atan2(p.y, p.x);
	pair<double, double> pla = pair<double, double>(normalize_angle(a - ta), normalize_angle(a + ta));
#ifdef DEBUG
	cout << "angles of lines perpendicular to the tangent line from (" << p.x << ", " << p.y << ") = (" <<
		pla.first << ", " << pla.second << ")\n";
#endif
	return pla;
}

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		point p1, p2;
		circle c;
		c.c.x = c.c.y = 0;
		cin >> p1.x >> p1.y >> p2.x >> p2.y >> c.r;
		line l;
		points_to_line(p1, p2, l);
		point cp;
		if (!closest_point(c.c, l, cp) || !point_in_box(cp, p1, p2) ||
			euclidean_distance(c.c, cp) >= c.r)
			// min. length of rope = euclidean distance between two points
			printf("%.3f\n", euclidean_distance(p1, p2));
		else {
			pair<double, double> tl1 = tangent_line(p1, c);
			pair<double, double> tl2 = tangent_line(p2, c);
			// calculate the angles of lines perpendicular to the tangent line
			pair<double, double> pla1 = angles_of_lines_perpendicular_to_tangent_line(p1, tl1.second);
			pair<double, double> pla2 = angles_of_lines_perpendicular_to_tangent_line(p2, tl2.second);
			// calculate the angles of the two arcs, each of which is between the tangent line from p1 and 
			// the one from p2, and choose the smaller one
			double aa = min(fabs(normalize_angle(pla1.first - pla2.second)),
				fabs(normalize_angle(pla1.second - pla2.first)));
#ifdef DEBUG
			cout << "smaller angle of the two arcs = " << aa << endl;
#endif
			// min. length of rope = shorter arc of the two + two tangent lines
			double d = c.r * aa + tl1.first + tl2.first;
			printf("%.3f\n", d);
		}
	}
	return 0;
}


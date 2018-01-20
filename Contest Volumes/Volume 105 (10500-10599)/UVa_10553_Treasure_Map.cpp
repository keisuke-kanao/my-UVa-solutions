
/*
	UVa 10553 - Treasure Map
	from Waterloo ACM Programming Contest September 20, 2003 Problem E: Treasure Map
		(http://plg1.cs.uwaterloo.ca/~acm00/030920/E.html)

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10553_Treasure_Map.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

#define EPSILON FLT_EPSILON /* DBL_EPSILON */

const double pi = 2.0 * acos(0.0); // 3.14159265358979323846

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

void generate_compass_points(map<string, double>& compass_points)
{
	const pair<string, double> cps[] = {
		make_pair("N", 0.5 * pi), make_pair("NbE", 0.4375 * pi), make_pair("NNE", 0.375 * pi), make_pair("NEbN", 0.3125 * pi),
		make_pair("NE", 0.25 * pi), make_pair("NEbE", 0.1875 * pi), make_pair("ENE", 0.125 * pi), make_pair("EbN", 0.0625 * pi),
		make_pair("E", 0.0), make_pair("EbS", -0.0625 * pi), make_pair("ESE", -0.125 * pi), make_pair("SEbE", -0.1875 * pi),
		make_pair("SE", -0.25 * pi), make_pair("SEbS", -0.3125 * pi), make_pair("SSE", -0.375 * pi), make_pair("SbE", -0.4375 * pi),
		make_pair("S", -0.5 * pi), make_pair("SbW", -0.5625 * pi), make_pair("SSW", -0.625 * pi), make_pair("SWbS", -0.6875 * pi),
		make_pair("SW", -0.75 * pi), make_pair("SWbW", -0.8125 * pi), make_pair("WSW", -0.875 * pi), make_pair("WbS", -0.9375 * pi),
		make_pair("W", pi), make_pair("WbN", 0.9375 * pi), make_pair("WNW", 0.875 * pi), make_pair("NWbW", 0.8125 * pi),
		make_pair("NW", 0.75 * pi), make_pair("NWbN", 0.6875 * pi), make_pair("NNW", 0.625 * pi), make_pair("NbW", 0.5625 * pi)
	};
	for (size_t i = 0, n = sizeof(cps) / sizeof(pair<string, double>); i < n; i++)
		compass_points.insert(cps[i]);
}

void convert_to_point(double angle, int distance, point& p)
{
	p.x += cos(angle) * distance;
	p.y += sin(angle) * distance;
}

void convert_to_point(double angle, int distance, const point& previous, point& current)
{
	current.x = previous.x + cos(angle) * distance;
	current.y = previous.y + sin(angle) * distance;
}

int main(int /* argc */, char** /* argv */)
{
	map<string, double> compass_points;
	generate_compass_points(compass_points);
	while (true) {
		int nr_steps; // number of steps
		cin >> nr_steps;
		if (!nr_steps)
			break;
		vector<double> angles(nr_steps + 1);
		vector<int> paces(nr_steps + 1);
		angles[0] = 0.0; paces[0] = 0;
		point x; // point marked X where the treasure is located
		for (int i = 0; i < nr_steps; i++) {
			string cp; // compass point
			cin >> cp >> paces[i + 1];
			// get an angle (between -pi and pi) for the compass_point, and then
			// get the point coordinates from the angle, and the paces
			convert_to_point(angles[i + 1] = compass_points[cp], paces[i + 1], x);
		}
		double degree; // degree from north
		cin >> degree;
		double angle = degree * pi / 180.0; // convert to the angle in radian
		vector<point> points(nr_steps + 1);
		points[0].x = points[0].y = 0.0; // the first point is the original point
		for (int i = 0; i < nr_steps; i++) // rotate points by the angle
			convert_to_point(angles[i + 1] + angle, paces[i + 1], points[i], points[i + 1]);
		double least_distance = euclidean_distance(points[0], x);
		for (int i = 0; i < nr_steps; i++) {
			// get the closest point on the line segment from x
			point closest_p;
			double distance = (closest_point_from_line_segment(x, points[i], points[i + 1], closest_p)) ?
				euclidean_distance(closest_p, x) :
				min(euclidean_distance(points[i], x), euclidean_distance(points[i + 1], x));
			least_distance = min(least_distance, distance);
		}
		printf("%.2f\n", least_distance);
	}
	return 0;
}


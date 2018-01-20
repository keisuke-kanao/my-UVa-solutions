
/*
	14.7.4 Hotter Colder
	PC/UVa IDs: 111404/10084, Popularity: C, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10084_Hotter_Colder.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

/*
	Define a polygon, whose initial points are the vertices of the square.
	For each pair of succesive hotter/colder points:
		Rotate the two points by pi / 2 with respect to their midpoint.
		Get a line that connects the two (rotated) points.
		For each pair succesive points p1, p2 in the polygon:
			Add a point at which the line and the line segment made from p1 and p2.
			See if p1 lies to the right of the directed line which goes from the colder points to the hotter points:
				If not, remove p1.
*/

#define EPSILON FLT_EPSILON /* DBL_EPSILON */

const double pi = 2.0 * acos(0.0); // 3.14159265358979323846

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

ostream& operator<<(ostream& os, const point& p)
{
	os << '(' << p.x << ", " << p.y << ')';
	return os;
}

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

struct line_segment {
	point p1, p2;
	line_segment(const point& _p1, const point& _p2) : p1(_p1), p2(_p2) {}
};

bool left_lower(const point& p1, const point& p2)
{
	if (p1.x < p2.x)
		return true;
	else if (p1.x > p2.x)
		return false;
	else if (p1.y < p2.y)
		return true;
	else
		return false;
}

void sort_and_remove_duplicates(vector<point>& points, bool (*compare)(const point&, const point&) /* = left_lower */)
{
	sort(points.begin(), points.end(), compare); // sort the points in leftmost-lowest order
	for (vector<point>::iterator i = points.begin(); i != points.end(); ) { // remove the duplicate points
		vector<point>::iterator j = i;
		j++;
		if (j != points.end() && *i == *j)
			i = points.erase(i);
		else
			i++;
	}
}

double signed_triangle_area(const point& a, const point& b, const point& c)
{
	return (a.x * b.y - a.y * b.x + a.y * c.x - a.x * c.y + b.x * c.y - c.x * b.y) / 2.0;
}

bool collinear(const point& a, const point& b, const point& c)
{
	return fabs(signed_triangle_area(a, b, c)) <= EPSILON;
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool ccw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the left of a -> b (or, a - b - c are counterclockwise)
	return signed_triangle_area(a, b, c) > EPSILON;
}

bool cw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the right of a -> b (or, a - b - c are clockwise)
	return signed_triangle_area(a, b, c) < -EPSILON;
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& p1, const point& p2) const;
};

bool smaller_angle::operator() (const point& p1, const point& p2) const
{
	if (collinear(first, p1, p2))
		return euclidean_distance(first, p1) <= euclidean_distance(first, p2);
	else
		return ccw(first, p1, p2);
}

void print_polygon(const vector<point>& points)
{
	for (vector<point>::const_iterator i = points.begin(); i != points.end(); i++)
		cout << *i << endl;
}

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
	return p.x >= min(b1.x ,b2.x) && p.x <= max(b1.x ,b2.x) &&
		p.y >= min(b1.y, b2.y) && p.y <= max(b1.y, b2.y);
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

bool line_segments_intersect(const line_segment& s, const line& l, point& p)
{
	line ls;
	points_to_line(s.p1, s.p2, ls);
	if (same_lineQ(ls, l)) // overlapping or disjoint segments
		return false; 
	if (parallelQ(ls, l))
		return false;
	intersection_point(ls, l, p);
	return point_in_box(p, s.p1, s.p2);
}

double polygon_area(const vector<point>& polygon)
{
	double area = 0.0;
	for (int i = 0; i < polygon.size(); i++) {
		int j = (i + 1) % polygon.size();
		area += polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y;
	}
	return area / 2.0;
}

void sort_polygon_points(vector<point>& points) // sort the points of a polygon in a counterclockwise order
{
	sort_and_remove_duplicates(points, left_lower);
	vector<point>::iterator i = points.begin();
	i++;
	sort(i, points.end(), smaller_angle(points[0])); // sort the second and later points in increasing angular order
	if (points.size() > 2) { // remove the collinear points
		i = points.begin();
		for (i++; i != points.end() - 1; ) {
			if (collinear(*(i - 1), *i, *(i + 1)))
				i = points.erase(i);
			else
				i++;
		}
		if (points.size() > 2 && collinear(*(i - 1), *i, *points.begin()))
			points.erase(i);
	}
}

void rotate_point(const point& p, const point& c, double rangle, point& rp)
{
// rotate p by rangle with respect to c
	point q(p.x - c.x, p.y - c.y);
	double r = sqrt(q.x * q.x + q.y * q.y);
	double angle = atan2(q.y, q.x);
	rp.x = c.x + r * cos(angle + rangle);
	rp.y = c.y + r * sin(angle + rangle);
}

int main(int /* argc */, char** /* argv */)
{
	// define a polygon, whose initial points are the vertices of the square.
	vector<point> polygon;
	polygon.push_back(point(0.0, 0.0));
	polygon.push_back(point(10.0, 0.0));
	polygon.push_back(point(0.0, 10.0));
	polygon.push_back(point(10.0, 10.0));
	sort_polygon_points(polygon);
	point previous_p(0.0, 0.0);
	string sline;
	while (getline(cin, sline)) {
		istringstream iss(sline);
		point p;
		string s;
		iss >> p.x >> p.y >> s;
		point mid_p((previous_p.x + p.x) / 2, (previous_p.y + p.y) / 2), hotter_p, colder_p;
		// rotate the two points by pi / 2 with respect to their midpoint
		if (s == "Hotter") { // the current point is hotter
			rotate_point(previous_p, mid_p, pi / 2, colder_p);
			rotate_point(p, mid_p, pi / 2, hotter_p);
		}
		else { // the previous point is hotter/same
			rotate_point(p, mid_p, pi / 2, colder_p);
			rotate_point(previous_p, mid_p, pi / 2, hotter_p);
		}
#if DEBUG
		cout << "\nhotter = " << hotter_p << ", colder = " << colder_p << endl;
#endif
		// define a line segment that connects the two (rotated) points
		line l;
		points_to_line(colder_p, hotter_p, l);
		for (int i = 0, size = polygon.size(); i < size; i++) {
			// for each pair of succesive points in the polygon, add a point at which the two line segments intersect
			line_segment ls(polygon[i], polygon[(i + 1) % size]);
			point isp;
			if (line_segments_intersect(ls, l, isp))
				polygon.push_back(isp);
		}
#if DEBUG
		cout << "before removing points:\n";
		print_polygon(polygon);
#endif
		// for each point in the polygon, see if the point lies to the left of the directed line 
		// which goes from the colder points to the hotter points, and if so, remove the point from the polygon
		for (vector<point>::iterator i = polygon.begin(); i != polygon.end(); ) {
			bool result = (s == "Same") ? !collinear(colder_p, hotter_p, *i) : ccw(colder_p, hotter_p, *i);
			if (result)
				i = polygon.erase(i);
			else
				i++;
		}
		sort_polygon_points(polygon);
#if DEBUG
		cout << "after removing points:\n";
		print_polygon(polygon);
#endif
		printf("%.2f\n", polygon_area(polygon));
		previous_p = p;
	}
	return 0;
}

